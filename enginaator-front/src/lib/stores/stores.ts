import { writable } from 'svelte/store';

// Environmental metrics
export const ohuTemp = writable(1);
export const ohuNiiskus = writable(1);

// Plant metrics
export const valguseTaseWrite = writable(1);
export const mullaNiiskusWrite = writable(1);

// Store the polling interval ID
let pollInterval: number | null = null;


export async function fetchLastLightValue() {
  try {
    const response = await fetch('http://localhost:5000/api/data');
    
    if (!response.ok) {
      throw new Error(`HTTP error! Status: ${response.status}`);
    }
    
    const jsonData = await response.json();
    
    // Extract all keys containing "valgus"
    const valgusKeys = Object.keys(jsonData).filter(key => key.includes('valgus'));
    const muldKeys = Object.keys(jsonData).filter(key => key.includes('muld'));
    const niiskusKeys = Object.keys(jsonData).filter(key => key.includes('niiskus'));
    const tempKeys = Object.keys(jsonData).filter(key => key.includes('temp'));
    
    if (valgusKeys.length === 0 || muldKeys.length === 0 || niiskusKeys.length === 0 || tempKeys.length === 0) {
      return null;
    }
    
    // Get the last key - we'll use sorting to find the highest numbered key
    // Extract the number from each key if possible
    const keyWithNumbersValgus = valgusKeys.map(key => {
      const matches = key.match(/valgus(\d+)/);
      const num = matches ? parseInt(matches[1]) : 0;
      return { key, num };
    });

    const keyWithNumbersMuld = muldKeys.map(key => {
      const matches = key.match(/muld(\d+)/);
      const num = matches ? parseInt(matches[1]) : 0;
      return { key, num };
    });

    const keyWithNumbersNiiskus = niiskusKeys.map(key => {
      const matches = key.match(/niiskus(\d+)/);
      const num = matches ? parseInt(matches[1]) : 0;
      return { key, num };
    });

    const keyWithNumbersTemp = tempKeys.map(key => {
      const matches = key.match(/temp(\d+)/);
      const num = matches ? parseInt(matches[1]) : 0;
      return { key, num };
    });
    
    // Sort by the numeric part, descending
    keyWithNumbersValgus.sort((a, b) => b.num - a.num);
    keyWithNumbersMuld.sort((a, b) => b.num - a.num);
    keyWithNumbersNiiskus.sort((a, b) => b.num - a.num);
    keyWithNumbersTemp.sort((a, b) => b.num - a.num);
    
    // Get the key with the highest number (or first key if no numbers)
    const lastKeyValgus = keyWithNumbersValgus[0].key;
    const lastValueValgus = parseFloat(String(jsonData[lastKeyValgus]));

    const lastKeyMuld = keyWithNumbersMuld[0].key;
    const lastValueMuld = parseFloat(String(jsonData[lastKeyMuld]));

    const lastKeyNiiskus = keyWithNumbersNiiskus[0].key;
    const lastValueNiiskus = parseFloat(String(jsonData[lastKeyNiiskus]));

    const lastKeyTemp = keyWithNumbersTemp[0].key;
    const lastValueTemp = parseFloat(String(jsonData[lastKeyTemp]));

    
    return {
      valgus: isNaN(lastValueValgus) ? null : lastValueValgus,
      muld: isNaN(lastValueMuld) ? null : lastValueMuld,
      niiskus: isNaN(lastValueNiiskus) ? null : lastValueNiiskus,
      temp: isNaN(lastValueTemp) ? null : lastValueTemp
    };
  } catch (error) {
    console.error('Error fetching light data:', error);
    return null;
  }
}

/**
 * Start polling the API every 1 second and update the valguseTaseWrite store
 * @returns The interval ID
 */
export function startPolling(interval = 5000) {
  stopPolling();
  
  pollInterval = setInterval(async () => {
    const data = await fetchLastLightValue();
    if (data) {
      valguseTaseWrite.set(data.valgus ?? 1);
      mullaNiiskusWrite.set(data.muld ?? 1);
      ohuNiiskus.set(data.niiskus ?? 1);
      ohuTemp.set(data.temp ?? 1);
    }
  }, interval);
  
  return pollInterval;
}

/**
 * Stop polling the API
 */
export function stopPolling() {
  if (pollInterval !== null) {
    clearInterval(pollInterval);
    pollInterval = null;
  }
}

// Initialize light polling when this module is imported
startPolling();
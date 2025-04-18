// src/routes/stores.js
import { writable } from 'svelte/store';

// Environmental metrics
export let ohuTemp = writable(22);
export let ohuNiiskus = writable(45);

// Plant metrics
export let valguseTaseWrite = writable(60);
export let mullaNiiskusWrite = writable(900);
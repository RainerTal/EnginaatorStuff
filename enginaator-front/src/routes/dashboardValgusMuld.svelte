<script>
    import { Progress } from '@skeletonlabs/skeleton-svelte';
    import { valguseTaseWrite, mullaNiiskusWrite } from '../lib/stores/stores';

    // Example data - these would typically come from props or a store
    $: valgusTase = $valguseTaseWrite;
    let valgusTaseString = "";
    $: mullaNiiskus = $mullaNiiskusWrite;
    let mullaNiiskusString = "";

    $: if (valgusTase <= 20) {
      valgusTaseString = "Liiga pime";
    } else if (valgusTase <= 80) {
      valgusTaseString = "Normaalne";
    } else {
      valgusTaseString = "Liiga valge";
    }

    $: if (mullaNiiskus >= 2500) {
      mullaNiiskusString = "Liiga kuiv";
    } else if (mullaNiiskus >= 800) {
      mullaNiiskusString = "Normaalne";
    } else {
      mullaNiiskusString = "Liiga niiske";
    }
  </script>
  
  <div class="min-h-screen p-6">
    
    <!-- Main Content - Changed to stack vertically -->
    <div class="flex flex-col gap-6 max-w-md mx-auto">
      <!--  Valguse card -->
      <div class="bg-white rounded-lg shadow p-6">
        <div class="flex items-center justify-between">
          <h2 class="text-lg font-medium text-gray-600">Valgustase</h2>
          <!-- Valguse icon -->
          <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="currentColor" class="size-6 stroke-amber-400">
            <path stroke-linecap="round" stroke-linejoin="round" d="m3.75 13.5 10.5-11.25L12 10.5h8.25L9.75 21.75 12 13.5H3.75Z" />
          </svg>
          
          
        </div>
        <div class="mt-4">
          <span class="text-4xl font-semibold text-gray-800">{valgusTaseString}</span>
        </div>
        <div class="mt-4">
          <Progress 
          value={valgusTase} 
          max={100} 
          meterBg={valgusTase <= 20 || valgusTase >= 80 ? "bg-red-500" : "bg-green-500"} 
          trackBg="bg-gray-300" 
        />
        </div>
      </div>
      
      <!-- Mullaniiskuse Card -->
      <div class="bg-white rounded-lg shadow p-6">
        <div class="flex items-center justify-between">
          <h2 class="text-lg font-medium text-gray-600">Mullaniiskus</h2>
          <!-- Humidity icon -->
          <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="currentColor" class="size-6 stroke-green-800">
            <path stroke-linecap="round" stroke-linejoin="round" d="M12.75 3.03v.568c0 .334.148.65.405.864l1.068.89c.442.369.535 1.01.216 1.49l-.51.766a2.25 2.25 0 0 1-1.161.886l-.143.048a1.107 1.107 0 0 0-.57 1.664c.369.555.169 1.307-.427 1.605L9 13.125l.423 1.059a.956.956 0 0 1-1.652.928l-.679-.906a1.125 1.125 0 0 0-1.906.172L4.5 15.75l-.612.153M12.75 3.031a9 9 0 0 0-8.862 12.872M12.75 3.031a9 9 0 0 1 6.69 14.036m0 0-.177-.529A2.25 2.25 0 0 0 17.128 15H16.5l-.324-.324a1.453 1.453 0 0 0-2.328.377l-.036.073a1.586 1.586 0 0 1-.982.816l-.99.282c-.55.157-.894.702-.8 1.267l.073.438c.08.474.49.821.97.821.846 0 1.598.542 1.865 1.345l.215.643m5.276-3.67a9.012 9.012 0 0 1-5.276 3.67m0 0a9 9 0 0 1-10.275-4.835M15.75 9c0 .896-.393 1.7-1.016 2.25" />
          </svg>          
        </div>
        <div class="mt-4">
          <span class="text-4xl font-semibold text-gray-800">{mullaNiiskusString}</span>
        </div>
        <div class="mt-4">
          <Progress 
          value={4095 - mullaNiiskus} 
          max={4095} 
          meterBg={mullaNiiskus >= 2500 || mullaNiiskus < 800 ? "bg-red-500" : "bg-green-500"} 
          trackBg="bg-gray-300" 
        />
        </div>
      </div>
    </div>
  </div>
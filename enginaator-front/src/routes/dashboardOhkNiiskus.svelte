<script>
    import { ohuTemp, ohuNiiskus } from '../lib/stores/stores';
    // Example data - these would typically come from props or a store
    $: airTemperature = $ohuTemp;
    $: humidity = $ohuNiiskus;

  </script>
  
  <div class="min-h-screen p-6">
    
    <!-- Main Content - Changed to stack vertically -->
    <div class="flex flex-col gap-6 max-w-md mx-auto">
      <!-- Air Temperature Card -->
      <div class="bg-white rounded-lg shadow p-6">
        <div class="flex items-center justify-between">
          <h2 class="text-lg font-medium text-gray-600">Õhutemperatuur</h2>
          <!-- Temperature icon -->
          <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="currentColor" class="size-6 stroke-blue-400">
            <path stroke-linecap="round" stroke-linejoin="round" d="M2.25 15a4.5 4.5 0 0 0 4.5 4.5H18a3.75 3.75 0 0 0 1.332-7.257 3 3 0 0 0-3.758-3.848 5.25 5.25 0 0 0-10.233 2.33A4.502 4.502 0 0 0 2.25 15Z" />
          </svg>
          
        </div>
        <div class="mt-4">
          <span class="text-4xl font-semibold text-gray-800">{airTemperature}°C</span>
        </div>
      </div>
      
      <!-- Humidity Card -->
      <div class="bg-white rounded-lg shadow p-6">
        <div class="flex items-center justify-between">
          <h2 class="text-lg font-medium text-gray-600">Õhuniiskus</h2>
          <!-- Humidity icon -->
          <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="currentColor" class="size-6 stroke-blue-400">
            <path stroke-linecap="round" stroke-linejoin="round" d="M2.25 15a4.5 4.5 0 0 0 4.5 4.5H18a3.75 3.75 0 0 0 1.332-7.257 3 3 0 0 0-3.758-3.848 5.25 5.25 0 0 0-10.233 2.33A4.502 4.502 0 0 0 2.25 15Z" />
          </svg>
        </div>
        <div class="mt-4">
          <span class="text-4xl font-semibold text-gray-800">{humidity}%</span>
        </div>
      </div>
    </div>
  </div>
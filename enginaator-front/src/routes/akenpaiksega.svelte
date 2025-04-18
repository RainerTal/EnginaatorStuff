<script>
  import { valguseTaseWrite, mullaNiiskusWrite } from '../lib/stores/stores';

  export let windowFrameColor = "bg-amber-900"; // Tailwind color class for frame
  export let windowFrameWidth = "15";
  export let sunCorner = "top-right"; 

  $: isPlantHealthy = !($valguseTaseWrite <= 20 || $valguseTaseWrite >= 80 || $mullaNiiskusWrite <= 800 || $mullaNiiskusWrite>= 2500);
  $: plantImage = isPlantHealthy ? 'alive.png' : 'dead.png';

  $: cornerClasses = {
    "top-right": "top-0 right-0",
  }[sunCorner] || "top-0 right-0";

  $: sunTransform = {
    "top-right": "translate(60px, -60px)",
  }[sunCorner] || "translate(60px, -60px)";

  $: valueBoxPosition = {
    "top-right": "top-3/4 left-1/4",
  }[sunCorner] || "top-3/4 left-1/4";
</script>

<!-- Wall background -->
<div class={`fixed inset-0 bg-[url('redbrick.jpg')] flex items-center justify-center`} style="background-size: 1000px 700px;">
  <!-- Window frame -->
  <div class={`w-[40%] h-[80%] ${windowFrameColor} rounded-lg shadow-2xl p-[15px] grid grid-cols-2 grid-rows-2 gap-[15px]`} style="border-width: {windowFrameWidth}px;">
    <!-- Window content -->
    <div class="col-span-2 row-span-2 rounded relative overflow-hidden bg-cover bg-center" style="background-image: url('akenbg.jpg');">
      <!-- Overlay image on top of the background -->
      <div class="absolute inset-0 bg-cover bg-center z-10" style="background-image: url({plantImage}); background-size: contain; background-repeat: no-repeat; background-position: center;">
      </div>
      <!-- Sun container -->
      <div class={`absolute w-[200px] h-[200px] overflow-hidden ${cornerClasses}`}>
        <!-- Sun -->
        <div class="relative w-[200px] h-[200px] bg-amber-400 rounded-full shadow-lg" style="transform: {sunTransform};">
          <!-- Sun rays using a pseudo element with a background gradient -->
          <div class="absolute inset-0">
            <div class="absolute -inset-[50px]" style="
              background: repeating-conic-gradient(
                transparent 0deg,
                transparent 18deg,
                rgba(253, 184, 19, 0.7) 18deg, 
                rgba(253, 184, 19, 0.7) 20deg
              );
              border-radius: 50%;
              z-index: 1;
            "></div>
          </div>
        </div>
      </div>
    </div>
  </div>
</div>

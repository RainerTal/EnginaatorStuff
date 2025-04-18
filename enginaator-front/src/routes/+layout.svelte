<script lang="ts">
    import '../app.css';
    import Akenpaiksega from './akenpaiksega.svelte';
    import DashboardOhkNiiskus from './dashboardOhkNiiskus.svelte';
    import DashboardValgusMuld from './dashboardValgusMuld.svelte';
    import Alert from './alert.svelte';
    import { valguseTaseWrite, mullaNiiskusWrite } from '../lib/stores/stores';
	import Nupp from './nupp.svelte';
    
	let showAlert = $state(false);
    let message = $state(""); 

    $effect(() => {
        if (valguseTaseWrite && ($valguseTaseWrite <= 20)) {
			message = "Sinu taim on liiga pimedas asukohas! Tõsta see valgemasse alasse";
			showAlert = true;
		} else if (valguseTaseWrite && ($valguseTaseWrite >= 80)) {
			message = "Sinu taim on liiga valges asukohas! Tõsta see pimedamasse alasse";
			showAlert = true;
		} else if (mullaNiiskusWrite && ($mullaNiiskusWrite < 800)) {
			message = "Taime muld on liiga niiske! Ära kasta mõnda aega";
			showAlert = true;
		} else if (mullaNiiskusWrite && ($mullaNiiskusWrite > 2500)) {
			message = "Taime muld on liiga kuiv! Kasta esimesel võimalusel";
			showAlert = true;
		}
        }
    );
    
    let { children } = $props();
</script>

<div class="app">
    <Alert
        show={showAlert}
        message={message}
        duration={5000}
        position="top-center"
        onClose={() => showAlert = false}
    />
    <!-- Akenpaiksega as background (lowest z-index) -->
    <div class="fixed inset-0 z-0">
        <Akenpaiksega 
            sunCorner="top-right" 
            windowFrameColor="bg-yellow-950"
        />
    </div>

    <!-- Main content + dashboard on top -->
    <main class="relative z-10">
        <!-- Top content area -->
        <div class="p-4">
            {@render children()}
        </div>

       <!-- Dashboards container with flex layout -->
    <div class="flex w-full">
        <!-- Left Dashboard (1/4 width) -->
        <div class="w-1/4 p-4">
            <DashboardOhkNiiskus />
        </div>
        
        <!-- Center spacer -->
        <div class="flex-grow"></div>
        
        <!-- Right Dashboard (1/4 width) -->
        <div class="w-1/4 p-4">
            <DashboardValgusMuld />
        </div>
    </div>

	<div class="fixed bottom-7 left-1/2 transform -translate-x-1/2 z-20">
		<Nupp />
	</div>
    </main>
</div>

<style>

</style>

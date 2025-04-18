<script lang="ts">
    import { onMount } from 'svelte';

    // Props
    export let show = false;           // Whether to show the alert
    export let message = "";           // Alert message
    export let duration = 5000;        // Duration in ms (default 5s)
    export let position = "top-right"; // Position on screen
    export let onClose = () => {};     // Callback when alert closes

    let timer: ReturnType<typeof setTimeout> | null = null;
    
    $: if (show && duration > 0) {
        clearTimeout(timer as ReturnType<typeof setTimeout>);
        timer = setTimeout(() => {
            show = false;
            onClose();
        }, duration);
    }

    $: positionClasses = {
        "top-right": "top-4 right-4",
        "top-left": "top-4 left-4",
        "bottom-right": "bottom-4 right-4",
        "bottom-left": "bottom-4 left-4",
        "top-center": "top-4 left-1/2 transform -translate-x-1/2",
        "bottom-center": "bottom-4 left-1/2 transform -translate-x-1/2",
    }[position] || "top-4 right-4";

    onMount(() => {
        return () => {
            if (timer) clearTimeout(timer);
        };
    });
</script>

{#if show}
    <div 
        class="fixed {positionClasses} md:w-96 bg-amber-100 border-l-4 border-amber-500 text-amber-700 p-4 rounded shadow-lg z-50 transform transition-opacity duration-300 ease-in-out" 
        role="alert">
        <div class="flex items-center">
            <svg class="h-6 w-6 mr-4 text-amber-500" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 20 20" fill="currentColor" aria-hidden="true">
                <path fill-rule="evenodd" d="M8.257 3.099c.765-1.36 2.722-1.36 3.486 0l5.58 9.92c.75 1.334-.213 2.98-1.742 2.98H4.42c-1.53 0-2.493-1.646-1.743-2.98l5.58-9.92zM11 13a1 1 0 11-2 0 1 1 0 012 0zm-1-8a1 1 0 00-1 1v3a1 1 0 002 0V6a1 1 0 00-1-1z" clip-rule="evenodd"></path>
            </svg>
            <p class="font-medium">{message}</p>
        </div>
    </div>
{/if}
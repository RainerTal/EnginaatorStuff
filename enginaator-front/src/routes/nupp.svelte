<script lang="ts">
    // Props for the button
    export let text = "Peata alarm";
    export let type: "button" | "submit" | "reset" = "button"; // button, submit, reset
    export let size: "sm" | "md" | "lg" = "md"; // sm, md, lg
    export let onClick = () => {}; // click handler
    export let disabled = false;
    
    // Sizes for the button
    const sizes = {
      sm: "text-xs py-1.5 px-3",
      md: "text-sm py-3 px-6",
      lg: "text-base py-3 px-6"
    };
    
  </script>
  
  <button 
    type={type} 
    on:click={onClick} 
    {disabled}
    class="relative bg-gradient-to-r from-red-500 to-red-600 hover:from-red-600 hover:to-red-700 
    text-white font-medium rounded-lg {sizes[size]} transition-all duration-200 
    transform hover:scale-105 active:scale-95
    focus:outline-none focus:ring-2 focus:ring-offset-2 focus:ring-red-500
    shadow-lg shadow-red-500/30
    flex items-center justify-center gap-2"
    style="z-index: 15;">
    <span>{text}</span>
    <slot></slot>
  </button>
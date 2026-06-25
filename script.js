console.log("SCRIPT LOADED");

async function updateCounter() {
  try {
    const res = await fetch(
      "https://api.thingspeak.com/channels/3416860/fields/1/last.json",
    );

    const data = await res.json();

    document.getElementById("counterValue").innerText =
      `Wa wa wee wa, a whopping ${data.field1} times`;
  } catch (err) {
    console.log("FAILED:", err);
  }
}

updateCounter();
setInterval(updateCounter, 5000);

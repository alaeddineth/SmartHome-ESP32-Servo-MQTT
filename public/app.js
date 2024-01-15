document.addEventListener("DOMContentLoaded", function () {
  // Sample data
  const data = [10, 25, 18, 32, 24, 40, 30];

  // Get the canvas element and its context
  const canvas = document.getElementById("lineChart");
  const ctx = canvas.getContext("2d");

  // Set the canvas size
  canvas.width = 600;
  canvas.height = 400;

  // Draw the line chart
  drawLineChart(ctx, data);
});

function drawLineChart(ctx, data) {
  const canvasWidth = ctx.canvas.width;
  const canvasHeight = ctx.canvas.height;

  // Calculate the maximum value in the data array
  const maxDataValue = Math.max(...data);

  // Calculate the width and height of each bar
  const barWidth = canvasWidth / (data.length - 1);
  const scaleFactor = canvasHeight / maxDataValue;

  // Draw the line chart
  ctx.beginPath();
  ctx.moveTo(0, canvasHeight - data[0] * scaleFactor);

  for (let i = 1; i < data.length; i++) {
      ctx.lineTo(i * barWidth, canvasHeight - data[i] * scaleFactor);
  }

  // Style the line
  ctx.strokeStyle = "#3498db";
  ctx.lineWidth = 2;

  // Draw the line
  ctx.stroke();
}

    
const socket = io();

// Listen for resistance data updates from the server
socket.on('MOTORSERVO', (data) => {
  console.log("updates from the server  :")
    const resistanceValueElement = document.getElementById('resistanceValue');

  resistanceValueElement.textContent = `Resistance Value: ${data}`;

  
});

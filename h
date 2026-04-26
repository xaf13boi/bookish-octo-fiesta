<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Neon Runner</title>
<style>
html, body {
  margin: 0;
  padding: 0;
  background: black;
  overflow: hidden;
  font-family: Arial, sans-serif;
}
canvas {
  display: block;
  margin: auto;
  background: #111;
  box-shadow: 0 0 20px #0f0;
}
</style>
</head>
<body>

<canvas id="game"></canvas>

<script>
const canvas = document.getElementById("game");
const ctx = canvas.getContext("2d");

canvas.width = 600;
canvas.height = 300;

// PLAYER
let player = {
  x: 80,
  y: 220,
  w: 25,
  h: 25,
  dy: 0,
  jump: false
};

let gravity = 0.8;
let speed = 6;
let obstacles = [];
let score = 0;
let gameOver = false;

// CONTROLS
document.addEventListener("keydown", e => {
  if ((e.code === "Space" || e.code === "ArrowUp") && !player.jump) {
    player.dy = -14;
    player.jump = true;
  }
});

// SPAWN OBSTACLES
function spawnObstacle(){
  let height = Math.random() > 0.5 ? 20 : 40;
  obstacles.push({
    x: canvas.width,
    y: canvas.height - height - 20,
    w: 20,
    h: height
  });
}

// GAME LOOP
function update(){
  if(gameOver){
    ctx.fillStyle = "white";
    ctx.font = "30px Arial";
    ctx.fillText("GAME OVER", 200, 130);
    ctx.fillText("Score: " + score, 220, 170);
    ctx.font = "16px Arial";
    ctx.fillText("Refresh to restart", 210, 200);
    return;
  }

  ctx.fillStyle = "#111";
  ctx.fillRect(0, 0, canvas.width, canvas.height);

  // PLAYER PHYSICS
  player.y += player.dy;
  player.dy += gravity;

  if(player.y >= 220){
    player.y = 220;
    player.dy = 0;
    player.jump = false;
  }

  // DRAW PLAYER
  ctx.fillStyle = "#00ffcc";
  ctx.fillRect(player.x, player.y, player.w, player.h);

  // OBSTACLES
  for(let i = 0; i < obstacles.length; i++){
    let o = obstacles[i];
    o.x -= speed;

    ctx.fillStyle = "#ff0055";
    ctx.fillRect(o.x, o.y, o.w, o.h);

    // COLLISION
    if(player.x < o.x + o.w &&
       player.x + player.w > o.x &&
       player.y < o.y + o.h &&
       player.y + player.h > o.y){
      gameOver = true;
    }
  }

  // REMOVE OFFSCREEN
  obstacles = obstacles.filter(o => o.x > -20);

  // SCORE
  score++;
  ctx.fillStyle = "white";
  ctx.font = "16px Arial";
  ctx.fillText("Score: " + score, 10, 20);

  requestAnimationFrame(update);
}

// SPAWN LOOP
setInterval(spawnObstacle, 1200);

// START GAME
update();
</script>

</body>
</html>

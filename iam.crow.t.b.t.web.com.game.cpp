<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>I am Crow: The Biryani Thief</title>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/three.js/r128/three.min.js"></script>
    <style>
        body { 
            background: linear-gradient(135deg, #1e1e2f, #111119); 
            color: white; 
            font-family: 'Segoe UI', sans-serif; 
            text-align: center; 
            margin: 0;
            padding: 20px;
            overflow-x: hidden;
        }
        h1 { color: #ffcc00; margin: 5px 0; font-size: 2rem; }
        h3 { color: #a0a0ca; font-weight: 400; margin: 0 0 15px 0; }
        
        /* Logo Styling */
        .logo-container { margin: 10px auto; max-width: 180px; }
        .logo { max-width: 100%; border-radius: 10px; box-shadow: 0 4px 15px rgba(0,0,0,0.5); }
        
        /* 3D Game Canvas Area */
        #game-container {
            width: 100%;
            max-width: 600px;
            height: 350px;
            margin: 15px auto;
            border: 3px solid #ffcc00;
            border-radius: 15px;
            background-color: #000;
            position: relative;
            box-shadow: 0 8px 25px rgba(255, 204, 0, 0.2);
        }
        canvas { width: 100%; height: 100%; border-radius: 12px; display: block; }

        /* Mobile Controls Styling */
        .controls {
            display: grid;
            grid-template-columns: repeat(3, 60px);
            grid-gap: 10px;
            justify-content: center;
            margin: 15px auto;
            max-width: 300px;
        }
        .btn {
            background-color: #ffcc00;
            color: #111;
            border: none;
            padding: 15px;
            font-weight: bold;
            font-size: 1.1rem;
            border-radius: 10px;
            user-select: none;
            touch-action: manipulation;
        }
        .btn:active { background-color: #cca300; }
        .empty { visibility: hidden; }
    </style>
</head>
<body>

    <div class="logo-container">
        <img src="1000070631.png" alt="Crow Logo" class="logo" onerror="this.src='logo.png';">
    </div>

    <h1>🦅 I am Crow: The Biryani Thief 🍗</h1>
    <h3>Welcome to Sanvordem, Goa! (3D Pre-Alpha)</h3>

    <div id="game-container"></div>

    <div class="controls">
        <button class="btn" id="btn-up">🔺 Up</button>
        <button class="btn" id="btn-forward">🔼 Fwd</button>
        <button class="btn" id="btn-down">🔻 Dn</button>
        <button class="btn" id="btn-left">◀ Left</button>
        <button class="btn empty"></button>
        <button class="btn" id="btn-right">▶ Right</button>
        <button class="btn empty"></button>
        <button class="btn" id="btn-backward">🔽 Bak</button>
        <button class="btn empty"></button>
    </div>

    <p style="color: #a0a0ca; font-size: 0.9rem;">Guns, Biryani Handi, aur Goa Map agle update mein load honge! 🚀</p>

    <script>
        const container = document.getElementById('game-container');
        
        // Scene, Camera, Renderer Setup
        const scene = new THREE.Scene();
        scene.background = new THREE.Color(0x1a1a26);
        
        const camera = new THREE.PerspectiveCamera(75, container.clientWidth / container.clientHeight, 01, 1000);
        camera.position.set(0, 5, 10);
        camera.lookAt(0, 2, 0);

        const renderer = new THREE.WebGLRenderer({ antialias: true });
        renderer.setSize(container.clientWidth, container.clientHeight);
        container.appendChild(renderer.domElement);

        // Lights
        const ambientLight = new THREE.AmbientLight(0xffffff, 0.6);
        scene.add(ambientLight);
        const dirLight = new THREE.DirectionalLight(0xffffff, 0.8);
        dirLight.position.set(5, 10, 7);
        scene.add(dirLight);

        // 3D Ground (Sanvordem Market Base)
        const groundGeo = new THREE.PlaneGeometry(40, 40);
        const groundMat = new THREE.MeshStandardMaterial({ color: 0x2e5c1e, side: THREE.DoubleSide });
        const ground = new THREE.Mesh(groundGeo, groundMat);
        ground.rotation.x = -Math.PI / 2;
        scene.add(ground);

        // 3D Crow (Abhi ke liye ek temporary Red/Yellow Flying Object)
        const crowGeo = new THREE.ConeGeometry(0.8, 2, 4);
        const crowMat = new THREE.MeshStandardMaterial({ color: 0xff4444 });
        const crow = new THREE.Mesh(crowGeo, crowMat);
        crow.position.set(0, 3, 0);
        crow.rotation.x = Math.PI / 2; // Forward facing
        scene.add(crow);

        // Movement Logic
        const speed = 0.2;
        
        function move(direction) {
            if(direction === 'fwd') crow.position.z -= speed;
            if(direction === 'bak') crow.position.z += speed;
            if(direction === 'left') crow.position.x -= speed;
            if(direction === 'right') crow.position.x += speed;
            if(direction === 'up') crow.position.y += speed;
            if(direction === 'dn') if(crow.position.y > 0.5) crow.position.y -= speed;
        }

        // Mobile Buttons Events
        document.getElementById('btn-forward').addEventListener('pointerdown', () => move('fwd'));
        document.getElementById('btn-backward').addEventListener('pointerdown', () => move('bak'));
        document.getElementById('btn-left').addEventListener('pointerdown', () => move('left'));
        document.getElementById('btn-right').addEventListener('pointerdown', () => move('right'));
        document.getElementById('btn-up').addEventListener('pointerdown', () => move('up'));
        document.getElementById('btn-down').addEventListener('pointerdown', () => move('dn'));

        // Keyboard Controls (For Laptop)
        window.addEventListener('keydown', (e) => {
            if(e.key === 'w' || e.key === 'ArrowUp') move('fwd');
            if(e.key === 's' || e.key === 'ArrowDown') move('bak');
            if(e.key === 'a' || e.key === 'ArrowLeft') move('left');
            if(e.key === 'd' || e.key === 'ArrowRight') move('right');
            if(e.key === ' ') move('up');
            if(e.key === 'Shift') move('dn');
        });

        // Animation Loop
        function animate() {
            requestAnimationFrame(animate);
            // Kawwe ko thoda real look dene ke liye hawa mein upar-neeche float karate hain
            crow.position.y += Math.sin(Date.now() * 0.005) * 0.005;
            renderer.render(scene, camera);
        }
        
        // Handle window resize
        window.addEventListener('resize', () => {
            camera.aspect = container.clientWidth / container.clientHeight;
            camera.updateProjectionMatrix();
            renderer.setSize(container.clientWidth, container.clientHeight);
        });

        animate();
    </script>
</body>
</html>

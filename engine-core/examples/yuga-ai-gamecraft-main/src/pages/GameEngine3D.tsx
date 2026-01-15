import { Canvas } from '@react-three/fiber';
import { OrbitControls, Grid, Box, Sphere, Cylinder, PerspectiveCamera } from '@react-three/drei';
import { Button } from '@/components/ui/button';
import { Card } from '@/components/ui/card';
import { useState } from 'react';
import { useNavigate } from 'react-router-dom';
import { Plus, Box as BoxIcon, Circle, Cylinder as CylinderIcon, Play, Save, ArrowLeft } from 'lucide-react';

interface GameObject {
  id: string;
  type: 'box' | 'sphere' | 'cylinder';
  position: [number, number, number];
  color: string;
}

export default function GameEngine3D() {
  const navigate = useNavigate();
  const [objects, setObjects] = useState<GameObject[]>([
    { id: '1', type: 'box', position: [0, 0.5, 0], color: '#6366f1' },
    { id: '2', type: 'sphere', position: [2, 0.5, 0], color: '#f59e0b' },
  ]);

  const addObject = (type: 'box' | 'sphere' | 'cylinder') => {
    const newObject: GameObject = {
      id: Date.now().toString(),
      type,
      position: [Math.random() * 4 - 2, 0.5, Math.random() * 4 - 2],
      color: `#${Math.floor(Math.random()*16777215).toString(16)}`,
    };
    setObjects([...objects, newObject]);
  };

  return (
    <div className="h-screen flex flex-col bg-background">
      {/* Top Toolbar */}
      <div className="h-14 border-b border-border bg-card px-4 flex items-center justify-between">
        <div className="flex items-center gap-2">
          <Button
            variant="ghost"
            size="sm"
            onClick={() => navigate("/")}
            className="gap-2"
          >
            <ArrowLeft className="w-4 h-4" />
            Back
          </Button>
          <div className="h-6 w-px bg-border" />
          <img src="/logo.png" alt="YUGA" className="w-8 h-8" />
          <h1 className="text-lg font-bold">YUGA 3D Engine</h1>
        </div>
        <div className="flex gap-2">
          <Button size="sm" variant="outline" onClick={() => addObject('box')}>
            <BoxIcon className="w-4 h-4 mr-2" />
            Add Cube
          </Button>
          <Button size="sm" variant="outline" onClick={() => addObject('sphere')}>
            <Circle className="w-4 h-4 mr-2" />
            Add Sphere
          </Button>
          <Button size="sm" variant="outline" onClick={() => addObject('cylinder')}>
            <CylinderIcon className="w-4 h-4 mr-2" />
            Add Cylinder
          </Button>
          <Button size="sm" variant="default">
            <Play className="w-4 h-4 mr-2" />
            Play
          </Button>
          <Button size="sm" variant="default">
            <Save className="w-4 h-4 mr-2" />
            Save
          </Button>
        </div>
      </div>

      <div className="flex-1 flex">
        {/* 3D Viewport */}
        <div className="flex-1 relative">
          <Canvas shadows>
            <PerspectiveCamera makeDefault position={[5, 5, 5]} />
            <OrbitControls />
            
            {/* Lighting */}
            <ambientLight intensity={0.5} />
            <directionalLight
              position={[10, 10, 5]}
              intensity={1}
              castShadow
              shadow-mapSize-width={2048}
              shadow-mapSize-height={2048}
            />
            
            {/* Grid */}
            <Grid args={[20, 20]} cellColor="#6b7280" sectionColor="#4b5563" />
            
            {/* Ground Plane */}
            <mesh rotation={[-Math.PI / 2, 0, 0]} position={[0, 0, 0]} receiveShadow>
              <planeGeometry args={[20, 20]} />
              <meshStandardMaterial color="#1f2937" />
            </mesh>
            
            {/* Game Objects */}
            {objects.map((obj) => {
              if (obj.type === 'box') {
                return (
                  <Box key={obj.id} position={obj.position} castShadow>
                    <meshStandardMaterial color={obj.color} />
                  </Box>
                );
              }
              if (obj.type === 'sphere') {
                return (
                  <Sphere key={obj.id} position={obj.position} castShadow>
                    <meshStandardMaterial color={obj.color} />
                  </Sphere>
                );
              }
              if (obj.type === 'cylinder') {
                return (
                  <Cylinder key={obj.id} position={obj.position} castShadow>
                    <meshStandardMaterial color={obj.color} />
                  </Cylinder>
                );
              }
              return null;
            })}
          </Canvas>
          
          {/* Viewport Info */}
          <div className="absolute top-4 left-4">
            <Card className="p-3 bg-card/90 backdrop-blur">
              <div className="text-sm space-y-1">
                <div className="font-semibold">Scene Objects: {objects.length}</div>
                <div className="text-muted-foreground">
                  Left Click + Drag: Rotate
                </div>
                <div className="text-muted-foreground">
                  Right Click + Drag: Pan
                </div>
                <div className="text-muted-foreground">
                  Scroll: Zoom
                </div>
              </div>
            </Card>
          </div>
        </div>

        {/* Right Panel - Object Hierarchy */}
        <div className="w-64 border-l border-border bg-card p-4">
          <h3 className="font-semibold mb-4">Scene Hierarchy</h3>
          <div className="space-y-2">
            {objects.map((obj) => (
              <Card
                key={obj.id}
                className="p-2 cursor-pointer hover:bg-accent transition-colors"
              >
                <div className="flex items-center gap-2">
                  {obj.type === 'box' && <BoxIcon className="w-4 h-4" />}
                  {obj.type === 'sphere' && <Circle className="w-4 h-4" />}
                  {obj.type === 'cylinder' && <CylinderIcon className="w-4 h-4" />}
                  <span className="text-sm capitalize">{obj.type}</span>
                </div>
                <div className="text-xs text-muted-foreground mt-1">
                  Position: [{obj.position.map(p => p.toFixed(1)).join(', ')}]
                </div>
              </Card>
            ))}
          </div>
        </div>
      </div>
    </div>
  );
}

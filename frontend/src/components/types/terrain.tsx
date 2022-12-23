export interface TerrainValues {
    size: {
        width: number,
        height: number
    },
    config: {
        frequency: number,
        gain: number,
        lacunarity: number,
        octaves: number,
        seed: number
    }
    rotate: {
        angle_x: number,
        angle_y: number,
        angle_z: number
    }
    scale: number
}
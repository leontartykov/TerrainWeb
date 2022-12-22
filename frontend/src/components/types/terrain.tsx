export interface TerrainValues{
    size: {
        width: string,
        height: string
    },  
    config:{
        frequency: string,
        gain: string,
        lacunarity: string,
        octaves: string,
        seed: string
    }
    rotate:{
        angle_x: string,
        angle_y: string,
        angle_z: string
    }
    scale: string
}
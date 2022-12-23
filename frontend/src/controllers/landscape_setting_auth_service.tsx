import TerrainService from "services/terrain_service"
import React from "react"
import { LandscapeSettingsAuthComponent } from "components/pages/landscapeSettingsAuth"
import { TerrainValues } from "components/types/terrain"
import ProjectService from "services/projects_service"
import { Buffer } from 'buffer';

interface TerrainProject{
    name?: string
}

export default class LandscapeSettingAuthService extends React.Component<TerrainProject> {
    data: any = "";
    userName = sessionStorage.getItem("usrName");
    data_resp: any;
    /*terrain: TerrainValues = {
        size: { width: 0, height: 0 },
        config: { frequency: 0, gain: 0, lacunarity: 0, octaves: 0, seed: 0 },
        rotate: { angle_x: 0, angle_y: 0, angle_z: 0 }, scale: 0
    };*/
    image: string = "";
    terrain: any;
    nameProj: string = ""
    
    constructor(props: any) {
        super(props);
        this.getTerrainParams();
        console.log("brhrhr");
        console.log("proj_name: ", localStorage.getItem("project"));
        console.log()
    }

    async getTerrainParams() {
        let data_resp = await TerrainService.getParams("2", localStorage.getItem("project"));
        console.log("data_resp: ", data_resp);
        this.terrain = data_resp.data;
        this.setState({terrain: this.terrain});
    }

    setTerWidth(value: number) {
        this.terrain.size.width = +value
    }

    setTerHeight(value: number) {
        this.terrain.size.height = +value
    }

    setTerScale(value: number) {
        this.terrain.scale = +value
    }

    setTerFrequency(value: number) {
        this.terrain.config.frequency = +value
    }

    setTerGain(value: number) {
        this.terrain.config.gain = +value
    }

    setTerLacunarity(value: number) {
        this.terrain.config.lacunarity = +value
    }

    setTerOctaves(value: number) {
        this.terrain.config.octaves = +value
    }

    setTerSeed(value: number) {
        this.terrain.config.seed = +value
    }

    setTerRotateX(value: number) {
        this.terrain.rotate.angle_x = +value
    }

    setTerRotateY(value: number) {
        this.terrain.rotate.angle_y = +value
    }

    setTerRotateZ(value: number) {
        this.terrain.rotate.angle_z = +value
    }

    async handleGenerate(event: React.SyntheticEvent) {
        event.preventDefault();
        console.log("HANDLEGENERATE");
        console.log("get_width: ", this.terrain.size.width);
        console.log("get_height: ", this.terrain.size.height);
        if (this.terrain) {
            this.data = await ProjectService.RenderImage(this.terrain);
            console.log("render_image: ", this.data);
            this.setState({ mssg: "Hi there!" });
            this.render();
        }
    }

    async handleSaveProj(event: React.SyntheticEvent) {
        event.preventDefault();
        let data_resp = await TerrainService.saveParams("2", localStorage.getItem("project"), this.terrain);
    }

    render() {
        if (this.data.data) {
            console.log("here_yes")
            console.log("data_yes: ", this.data);
            let base64ImageString = Buffer.from(this.data.data, 'binary').toString('base64');
            console.log("base64ImageString: ", base64ImageString);
            return (<LandscapeSettingsAuthComponent
                terVals={this.terrain}
                userName={this.userName} image={base64ImageString}
                onClickGenerate={this.handleGenerate.bind(this)}
                onChangeTerWidth={event => this.setTerWidth(event.currentTarget.value)}
                onChangeTerHeight={event => this.setTerHeight(event.currentTarget.value)}
                onChangeTerScale={event => this.setTerScale(event.currentTarget.value)}
                onChangeTerFrequency={event => this.setTerFrequency(event.currentTarget.value)}
                onChangeTerGain={event => this.setTerGain(event.currentTarget.value)}
                onChangeTerLacunarity={event => this.setTerLacunarity(event.currentTarget.value)}
                onChangeTerOctaves={event => this.setTerOctaves(event.currentTarget.value)}
                onChangeTerSeed={event => this.setTerSeed(event.currentTarget.value)}
                onChangeTerRotateX={event => this.setTerRotateX(event.currentTarget.value)}
                onChangeTerRotateY={event => this.setTerRotateY(event.currentTarget.value)}
                onChangeTerRotateZ={event => this.setTerRotateZ(event.currentTarget.value)}
                onClickSaveproj={event => this.handleSaveProj(event.currentTarget.value)} />)
        } else if (this.terrain){
            console.log("here_no")
            return (<LandscapeSettingsAuthComponent
                userName={this.userName} terVals={this.terrain}
                onClickGenerate={this.handleGenerate.bind(this)}
                onChangeTerWidth={event => this.setTerWidth(event.currentTarget.value)}
                onChangeTerHeight={event => this.setTerHeight(event.currentTarget.value)}
                onChangeTerScale={event => this.setTerScale(event.currentTarget.value)}
                onChangeTerFrequency={event => this.setTerFrequency(event.currentTarget.value)}
                onChangeTerGain={event => this.setTerGain(event.currentTarget.value)}
                onChangeTerLacunarity={event => this.setTerLacunarity(event.currentTarget.value)}
                onChangeTerOctaves={event => this.setTerOctaves(event.currentTarget.value)}
                onChangeTerSeed={event => this.setTerSeed(event.currentTarget.value)}
                onChangeTerRotateX={event => this.setTerRotateX(event.currentTarget.value)}
                onChangeTerRotateY={event => this.setTerRotateY(event.currentTarget.value)}
                onChangeTerRotateZ={event => this.setTerRotateZ(event.currentTarget.value)}
                onClickSaveproj={this.handleSaveProj.bind(this)}></LandscapeSettingsAuthComponent>)
        }
    }
}


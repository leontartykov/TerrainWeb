import TerrainService from "services/terrain_service"
import React from "react"
import { LandscapeSettingsAuthComponent } from "components/pages/landscapeSettingsAuth"
import { TerrainValues } from "components/types/terrain"
import ProjectService from "services/projects_service"
import { Buffer } from 'buffer';

interface TerrainProject {
    name?: string
}

export default class LandscapeSettingAuthService extends React.Component<TerrainProject> {
    data: any = "";
    userName: string|null = sessionStorage.getItem("usrName");
    type_project: string|null = sessionStorage.getItem("type_project");
    data_resp: any;
    image: string = "";
    terrain: any;
    nameProj: string = "";
    is_my_project: boolean = false;
    error_generate: boolean = false;

    constructor(props: any) {
        super(props);
        this.getTerrainParams();
    }

    async getTerrainParams() {
        let data_resp;
        if (sessionStorage.getItem("checked_allProject")){
            console.log("checked allProject");
            this.userName = sessionStorage.getItem("checked_allProject");
            data_resp = await TerrainService.getRatingProjectParams(sessionStorage.getItem("project"));
            sessionStorage.removeItem("checked_allProject");
            this.terrain = data_resp.data;  
        }
        else{
            console.log("is not checked allProject");
            data_resp = await TerrainService.getParams(this.userName, sessionStorage.getItem("project"));
            this.terrain = data_resp.data;   
        }
        this.setState({ terrain: this.terrain });
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
        if (this.terrain) {
            this.data = await ProjectService.RenderImage(this.terrain);
            console.log("dataReturnGenerate: ", this.data);
            if (this.data != "400"){
                console.log("false");
                this.error_generate = false;
                
            }
            else{
                console.log("true");
                this.error_generate = true;
            }
            this.setState({ mssg: "Hi there!" });
        }
    }

    handleSaveProj(event: React.SyntheticEvent) {
        event.preventDefault();
        TerrainService.saveParams(this.userName, sessionStorage.getItem("project"), this.terrain);
    }

    async handleAddToRating(event: React.SyntheticEvent){
        event.preventDefault();
        console.log("handleAddToRating");
        console.log("event: ", event);
        await ProjectService.AddProjectToRating(this.userName, sessionStorage.getItem("project"));
    }

    handleLogout(){
        sessionStorage.removeItem("access_token");
        sessionStorage.removeItem("uuid");
        sessionStorage.removeItem("project");
        sessionStorage.removeItem("usrName");
    }

    handleRateProject(event: React.SyntheticEvent){
        //event.preventDefault();
        console.log("rateProject");
        console.log("this.userName: ", this.userName);
        ProjectService.RateProject(sessionStorage.getItem("project"), this.userName);
    }

    render() {
        this.type_project == "my" ? this.is_my_project = true :  this.is_my_project = false;
        console.log("this.is_my_project: ", this.is_my_project);
        console.log("this.error_generate: ", this.error_generate);

        if (this.data.data) {
            let base64ImageString = Buffer.from(this.data.data, 'binary').toString('base64');
            console.log("base64ImageString: ", base64ImageString);
            return (<LandscapeSettingsAuthComponent
                terVals={this.terrain} is_my_project={this.is_my_project} error_generate={this.error_generate}
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
                onClickSaveproj={event => this.handleSaveProj(event.currentTarget.value)}
                onClickAddToRating={this.handleAddToRating.bind(this)}
                onClickRateProject={this.handleRateProject.bind(this)} />)
        } else if (this.terrain) {
            return (<LandscapeSettingsAuthComponent
                userName={this.userName} terVals={this.terrain} is_my_project={this.is_my_project}  error_generate={this.error_generate}
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
                onClickSaveproj={this.handleSaveProj.bind(this)}
                onClickRateProject={this.handleRateProject.bind(this)}></LandscapeSettingsAuthComponent>)
        }
    }
}


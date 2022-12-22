import TerrainService from "services/terrain_service"
import React from "react"
import {LandscapeSettingsAuthComponent} from "components/pages/landscapeSettingsAuth"
import {TerrainValues} from "components/types/terrain"

export default class LandscapeSettingAuthService extends React.Component {
    data: any ="";
    userName = sessionStorage.getItem("usrName");
    data_resp: any;
    terrain: TerrainValues = {size:{width:"", height:""}, 
    config:{frequency: "", gain: "", lacunarity: "", octaves: "", seed: ""},
    rotate:{angle_x: "", angle_y:"", angle_z:""}, scale:""};

    constructor(props: any){
        super(props);
        this.getTerrainParams();    
    }

    async getTerrainParams(){
        
        console.log("getTerrainParams");
        this.data_resp = await TerrainService.getParams("2", "tatata");
        this.setState({data_resp : this.data_resp});
        this.terrain = this.data_resp.data;
        console.log("data_return: ", this.data_resp);
        console.log("terrain_data: ", this.terrain);
        this.render()
    }

    async handleGenerate(event: React.SyntheticEvent){
        event.preventDefault();
        console.log("HANDLEGENERATE");
        //this.data = await ProjectService.SetProjectCards();
        //console.log("data: ", this.data.data);
        //this.setState({ mssg: "Hi there!" });
    }

    

    render(){
        if (this.data.data){
            console.log("here_yes")
            console.log("data_yes: ", this.data);
            return (<LandscapeSettingsAuthComponent 
                    terVals={this.terrain}
                    userName={this.userName} image={this.data.data} onClickGenerate={this.handleGenerate.bind(this)}/>)
        }else{
        console.log("here_no")
        return (<LandscapeSettingsAuthComponent 
                userName={this.userName} terVals={this.terrain}
                onClickGenerate={this.handleGenerate.bind(this)}></LandscapeSettingsAuthComponent>)
        }
    }
}


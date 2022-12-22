import ProjectService from "services/projects_service"
import React from "react"
import {LandscapeSettingsAuthComponent} from "components/pages/landscapeSettingsAuth"

export default class LandscapeSettingAuthService extends React.Component {
    data: any ="";

    async handleGenerate(event: React.SyntheticEvent){
        event.preventDefault();
        console.log("HANDLEGENERATE");
        this.data = await ProjectService.SetProjectCards();
        console.log("data: ", this.data.data);
        this.setState({ mssg: "Hi there!" });
    }

    render(){
        if (this.data.data){
            console.log("here_yes")
            console.log("data_yes: ", this.data);
            return (<LandscapeSettingsAuthComponent image={this.data.data} onClickGenerate={this.handleGenerate.bind(this)}/>)
        }else{
        console.log("here_no")
        return (<LandscapeSettingsAuthComponent onClickGenerate={this.handleGenerate.bind(this)}></LandscapeSettingsAuthComponent>)
        }
    }
}


import React from "react"
import {MyProjectListAuthPageComponent} from "components/pages/myProjectListAuth"
import ProjectService from "services/projects_service"
import projectInfo from "components/types/projects"

export default class MyProjectListAuthService extends React.Component {
    page: string = "1";
    newProjName: string = "";
    projects: any;
    userName = sessionStorage.getItem("usrName");
    data_resp: any;
    is_projects: string = "no";
    needPageCard: string = "no";
    selectedMyProj: string = "";

    constructor(props: any){
        super(props);
        this.getFirstPage();    
    }

    async getFirstPage(){
        this.projects = await ProjectService.GetUserProjects("2", "1");
        this.setState({projects : this.projects});
    }

    setPage(value: string){
        this.page = value;
    }

    setNewProjName(value: string){
        this.newProjName = value;
    }

    setFoundMyProject(value: string){
        this.selectedMyProj = value;
    }

    async handlePage(event: React.SyntheticEvent){
        event.preventDefault();
        this.page = event.currentTarget.innerHTML;
        console.log("page: ", this.page);
        this.projects = await ProjectService.GetUserProjects("2", this.page);
        
        this.setState({ mssg: "Hi there!" });
        this.render();
    }

    handleDownload(event: React.SyntheticEvent){
        event.preventDefault();
        console.log("On handle Download.");
        console.log("id_download: ", event.currentTarget.id);
    }

    async handleDelete(event: React.SyntheticEvent){
        event.preventDefault();
        let projName = event.currentTarget.id;
        this.data_resp = await ProjectService.DeleteProject("2", projName);
        this.projects = await ProjectService.GetUserProjects("2", this.page);
        this.setState({ mssg: "Hi there!" });
        this.render();
    }

    async handleDeleteSelectedProjs(event: React.SyntheticEvent){

    }

    async handleAddProject(event: React.SyntheticEvent){
        event.preventDefault();
        console.log("Add project");
        console.log("this.newProjName: ", this.newProjName);
        if (this.newProjName){
            this.data_resp = await ProjectService.AddProject("2", this.newProjName);
            console.log(this.data_resp.status);
            if (this.data_resp.status == 409){
                let component = document.getElementById("createNewProjError");
                if (component){
                    component.innerText = "Такой проект уже существует!";
                }
            }
            else{
                let component = document.getElementById("createNewProjError");
                if (component){
                    component.innerText = "";
                }
                this.projects = await ProjectService.GetUserProjects("2", this.page);
                
                this.newProjName = ""
                this.setState({ mssg: "Hi there!" });
                this.render();
            }
        }
        else{
            let component = document.getElementById("createNewProjError");
            if (component){
                component.innerText = "Имя проекта должно быть непустым!";
            }
        }
    }

    async handleFindMyProj(event: KeyboardEvent){
        if (event.key === 'Enter'){
            if (this.selectedMyProj != ""){
                this.projects = await ProjectService.FindMyProject("2", this.selectedMyProj);
                
            }
            else{
                this.projects = await ProjectService.GetUserProjects("2", this.page);
            }
            this.setState({ mssg: "Hi there!" });
            this.render();
        }
    }

    render(){ 
        console.log("nnedpage: ", this.page);  
        console.log("this.projects_render: ", this.projects);    
        if (this.projects && this.projects.data){
            console.log("neww");
            this.is_projects = "yes";
            this.needPageCard = "yes";

            
            return (<MyProjectListAuthPageComponent 
                    isProjects={this.is_projects} userName={this.userName} activePage={+this.page} needPageCard={this.needPageCard}
                    onClickPage={this.handlePage.bind(this)} project1={this.projects.data[0] || this.projects.data}
                    project2={this.projects.data[1]} project3={this.projects.data[2]}
                    onChangeSearchMyProject={event => {this.setFoundMyProject(event.currentTarget.value)}}
                    onKeyPressSearchMyProject={this.handleFindMyProj.bind(this)}
                    onClickDownload={this.handleDownload.bind(this)}
                    onClickDelete={this.handleDelete.bind(this)}
                    onClickDeleteSelected={this.handleDeleteSelectedProjs.bind(this)}
                    onClickAddProject={this.handleAddProject.bind(this)}></MyProjectListAuthPageComponent>)
        }
        else{
            if (this.page != "1"){
                this.needPageCard = "yes";
            }

            return (
            <MyProjectListAuthPageComponent 
                isProjects={this.is_projects} userName={this.userName} activePage={+this.page} needPageCard={this.needPageCard}
                onClickPage={this.handlePage.bind(this)}
                onClickAddProject={this.handleAddProject.bind(this)}
                onChangeSearchMyProject={event => this.setNewProjName(event.currentTarget.value)}></MyProjectListAuthPageComponent>)
        }
    }
}
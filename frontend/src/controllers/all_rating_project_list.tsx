import React from "react"
import { AllProjectsPage } from "components/pages/allProjectsPage"
import ProjectService from "services/projects_service"

export default class AllProjectListService extends React.Component {
    projects: any;
    page: string = "1";
    is_projects: string = "no";
    needPageCard: string = "no";
    selectedProj: string = "";
    userName = sessionStorage.getItem("usrName");

    constructor(props: any) {
        super(props);
        this.getTerrainParams();
    }

    setProjectToFind(value: string) {
        this.selectedProj = value;
    }

    async getTerrainParams() {
        this.projects = await ProjectService.GetAllRatingProjects(this.page);
        console.log("this.projects: ", this.projects);
        this.setState({ projects: this.projects });
    }

    async handlePage(event: React.SyntheticEvent) {
        event.preventDefault();
        this.page = event.currentTarget.innerHTML;
        console.log("page: ", this.page);
        console.log("PAPGEPAGEPAGE");
        this.projects = await ProjectService.GetAllRatingProjects(this.page);

        this.setState({ mssg: "Hi there!" });
        this.render();
    }

    async handleFindProj(event: KeyboardEvent) {
        console.log("handleFindProj");
        if (event.key === 'Enter') {
            if (this.selectedProj != "") {
                this.projects = await ProjectService.FindProject(this.selectedProj);
            }
            else {
                this.projects = await ProjectService.GetAllRatingProjects(this.page);
            }
            this.setState({ mssg: "Hi there!" });
            this.render();
        }
    }

    async handleOnClickProject(value: any) {
        console.log("HANDLEONCLICK");
        sessionStorage.removeItem("type_project");
        sessionStorage.setItem("type_project", "all");
        console.log("propject: ", value.target.innerText);
        this.projects = await ProjectService.FindProject(value.target.innerText);
        console.log("projectsHANDLEONCCLICK: ", this.projects);
        sessionStorage.removeItem("checked_allProject");
        sessionStorage.setItem("checked_allProject: ", this.projects.data.userName);
        sessionStorage.removeItem("project");
        sessionStorage.setItem("project", value.target.innerText);
    }

    render() {
        console.log("al_terrains: ", this.projects);
        console.log("userNameAllProjs: ", this.userName);
        if (this.projects && this.projects.data) {
            console.log("neww");
            this.is_projects = "yes";
            this.needPageCard = "yes";
            return (<AllProjectsPage userName={this.userName}
                        isProjects={this.is_projects} activePage={+this.page} needPageCard={this.needPageCard}
                        onClickPage={this.handlePage.bind(this)} project1={this.projects.data[0] || this.projects.data}
                        project2={this.projects.data[1]} project3={this.projects.data[2]}
                        onChangeSearchMyProject={event => this.setProjectToFind(event.currentTarget.value)}
                        onKeyPressSearchMyProject={this.handleFindProj.bind(this)}
                        onClickHandleProject1={this.handleOnClickProject.bind(this)}
                        onClickHandleProject2={this.handleOnClickProject.bind(this)}
                        onClickHandleProject3={this.handleOnClickProject.bind(this)}></AllProjectsPage>)
        }

        if (this.page != "1") {
            this.needPageCard = "yes";
        }
        return (<AllProjectsPage userName={this.userName}
                isProjects={this.is_projects} activePage={+this.page} needPageCard={this.needPageCard}
                onClickPage={this.handlePage.bind(this)}
                onChangeSearchMyProject={event => this.setProjectToFind(event.currentTarget.value)}
                onKeyPressSearchMyProject={this.handleFindProj.bind(this)}></AllProjectsPage>)
    }
}
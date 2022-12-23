import http from "http_common"
import {TerrainValues} from "components/types/terrain"

async function RenderImage(terrain: TerrainValues) {
    if (terrain){
        console.log("terrain: ", terrain);
        const json = {
            terrain,
            light: { x: 500, y: 400, z: 500 }
        };
    
        const response = await
            http.post("api/v1/renderJobs/terrains/image",
                json)
                .then((response) => {
                    console.log(response.status);
                    return {
                        data: response?.data
                    };
                })
        return {
            data: response?.data
        };
    }
}

async function GetUserProjects(id_user: string, pageList: string) {
    const response = await
        http.get("api/v1/users/" + id_user + "/projects?page=" + pageList).then((response) => {
            return {
                data: response?.data
            }
        }
        )
    return {
        data: response?.data
    }
}

async function DeleteProject(id_user: string, id_project: string) {
    const response = await
        http.delete("api/v1/users/" + id_user + "/projects/" + id_project).then((response) => {
            return {
                status: response?.status
            }
        })
    return {
        status: response?.status
    }
}

async function AddProject(id_user: string, proj_name: string) {
    const response = await
        http.post("api/v1/users/" + id_user + "/projects", { name: proj_name }).then((response) => {
            console.log("statusTHEN: ", response?.status);
            return {
                status: response?.status
            }
        }).catch((error) => {
            return {
                status: error.response?.status
            }
        })
    return {

        status: response?.status
    }
}

async function FindMyProject(id_user: string, proj_name: string) {
    const response = await
        http.get("api/v1/users/" + id_user + "/projects/"+proj_name).then((response) => {
            console.log("statusTHEN: ", response?.status);
            return {
                data: response?.data
            }
        }).catch((error) => {
            return {
                data: error.response?.status
            }
        })
    return {
        data: response?.data
    }
}

const ProjectService = {
    RenderImage,
    GetUserProjects,
    DeleteProject,
    AddProject,
    FindMyProject
};

export default ProjectService;
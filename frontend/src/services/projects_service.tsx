import http from "http_common"
import { TerrainValues } from "components/types/terrain"

async function RenderImage(terrain: TerrainValues) {
    if (terrain) {
        console.log("terrain: ", terrain);
        const json = {
            terrain,
            light: { x: 100, y: 100, z: 100 }
        };

        const response = await
            http.post("api/v1/renderJobs/terrains/image",
                json, { responseType: "arraybuffer" })
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

async function GetUserProjects(userName: string | null, pageList: string) {
    console.log("userNameGetUserProjects: ", userName);
    //console.log("access_token: ", sessionStorage.getItem("access_token"));
    const response = await
        http.get("api/v1/users/" + userName + "/myProjects?page=" + pageList, 
                { headers: {'Authorization': sessionStorage.getItem("access_token"),
                            'uuid': sessionStorage.getItem("uuid")}}).then((response) => {
            return {
                data: response?.data
            }
        }
        )
    return {
        data: response?.data
    }
}

async function DeleteProject(userName: string | null, id_project: string) {
    const response = await
        http.delete("api/v1/users/" + userName + "/myProjects/" + id_project).then((response) => {
            return {
                status: response?.status
            }
        })
    return {
        status: response?.status
    }
}

async function AddProject(userName: string | null, proj_name: string) {
    const response = await
        http.post("api/v1/users/" + userName + "/myProjects", { name: proj_name }).then((response) => {
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

async function FindMyProject(userName: string | null, proj_name: string) {
    const response = await
        http.get("api/v1/users/" + userName + "/myProjects/" + proj_name).then((response) => {
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

async function AddProjectToRating(userName: string | null, proj_name: string | null) {
    const response = await
        http.get("api/v1/users/" + userName + "/myProjects/" + proj_name).then((response) => {
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

async function GetAllRatingProjects(page: string) {
    const response = await
        http.get("api/v1/allProjects?page="+page).then((response) => {
            return {
                data: response?.data
            }
        }
        )
    return {
        data: response?.data
    }
}

async function FindProject(proj_name: string) {
    const response = await
        http.get("api/v1/allProjects/"+proj_name).then((response) => {
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

async function RateProject(proj_name: string|null, user_name: string|null){
    const response = await
        http.post("api/v1/ratingJobs/projects/"+proj_name+"/rate", { userName: user_name }).then((response) => {
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
    FindMyProject,
    AddProjectToRating,
    GetAllRatingProjects,
    FindProject,
    RateProject
};

export default ProjectService;
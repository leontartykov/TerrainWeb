import http from "http_common"
import { TerrainValues } from "components/types/terrain"

async function RenderImage(terrain: TerrainValues) {
    if (terrain && check_params(terrain)) {
        console.log("terrain: ", terrain);
        const json = {
            terrain,
            light: { x: 500, y: 1000, z: 1000 }
        };

        const response = await
            http.post("api/v1/renderJobs/terrains/image",
                json, {
                    responseType: "arraybuffer",
                headers: {
                    'Authorization': sessionStorage.getItem("access_token"),
                    'uuid': sessionStorage.getItem("uuid")
                }
            })
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
    return "400";
}

function check_params(terrain: TerrainValues){
    let success = 0;
    if (terrain.config.frequency > 0 && terrain.config.gain > 0 && terrain.config.lacunarity && terrain.config.octaves && terrain.config.seed &&
        terrain.rotate.angle_x >= 0 && terrain.rotate.angle_y >= 0 && terrain.rotate.angle_z >= 0 &&
        terrain.scale > 0 && terrain.size.width > 0 && terrain.size.height > 0){
            success = 1;
        }
    return success;
}

async function GetUserProjects(userName: string | null, pageList: string) {
    console.log("access_token: ", sessionStorage.getItem("access_token"));
    console.log("uuid: ", sessionStorage.getItem("uuid"));
    console.log("username: ", userName)
    const response = await
        http.get("api/v1/users/" + userName + "/myProjects?page=" + pageList,
            {
                headers: {
                    'Authorization': sessionStorage.getItem("access_token"),
                    'uuid': sessionStorage.getItem("uuid")
                }
            }).then((response) => {
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
        http.delete("api/v1/users/" + userName + "/myProjects/" + id_project,
            {
                headers: {
                    'Authorization': sessionStorage.getItem("access_token"),
                    'uuid': sessionStorage.getItem("uuid")
                }
            }
        ).then((response) => {
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
        http.post("api/v1/users/" + userName + "/myProjects",
            { name: proj_name },
            {
                headers: {
                    'Authorization': sessionStorage.getItem("access_token"),
                    'uuid': sessionStorage.getItem("uuid")
                }
            }
        ).then((response) => {
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
        http.get("api/v1/users/" + userName + "/myProjects/" + proj_name,
            {
                headers: {
                    'Authorization': sessionStorage.getItem("access_token"),
                    'uuid': sessionStorage.getItem("uuid")
                }
            })
            .then((response) => {
                console.log("statusTHEN: ", response?.status);
                return {
                    data: response?.data
                }
            })
            .catch((error) => {
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
        http.post("api/v1/ratingJobs/users/" + userName + "/myProjects/" + proj_name+"/addToRating",
            {
                headers: {
                    'Authorization': sessionStorage.getItem("access_token"),
                    'uuid': sessionStorage.getItem("uuid")
                }
            })
            .then((response) => {
                return {
                    status: response?.status
                }
            })
            .catch((error) => {
                return {
                    status: error.response?.status
                }
            })
    return {
        status: response?.status
    }
}

async function GetAllRatingProjects(page: string) {
    console.log("GetAllRatingProjects");
    const response = await
        http.get("api/v1/allProjects?page=" + page,
            {
                headers: {
                    'Authorization': sessionStorage.getItem("access_token"),
                    'uuid': sessionStorage.getItem("uuid")
                }
            })
            .then((response) => {
                return {
                    data: response?.data
                }
            })
    return {
        data: response?.data
    }
}

async function FindProject(proj_name: string) {
    console.log("proj_nameFIND_PROJECT: ", proj_name);
    const response = await
        http.get("api/v1/allProjects/" + proj_name,
            {
                headers: {
                    'Authorization': sessionStorage.getItem("access_token"),
                    'uuid': sessionStorage.getItem("uuid")
                }
            })
            .then((response) => {
                console.log("statusTHEN: ", response?.status);
                return {
                    data: response?.data
                }
            }).catch((error) => {
                console.log("errorFind_project: ", error.response?.status);
                return {
                    data: error.response?.status
                }
            })
    
    return {
        data: response?.data
    }
}

async function RateProject(proj_name: string | null, user_name: string | null) {
    const response = await
        http.post("api/v1/ratingJobs/projects/" + proj_name + "/rate", { userName: user_name },
            {
                headers: {
                    'Authorization': sessionStorage.getItem("access_token"),
                    'uuid': sessionStorage.getItem("uuid")
                }
            })
            .then((response) => {
                console.log("statusTHEN: ", response?.status);
                return {
                    data: response?.data
                }
            })
            .catch((error) => {
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
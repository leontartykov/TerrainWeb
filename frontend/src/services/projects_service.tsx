import http from "http_common"

async function SetProjectCards() {
    let width: number = 100;
    let height: number = 150;
    let scale: number = 1;
    let octaves: number = 6;
    let gain: number = 0.35;
    let lacunaity: number = 2.3;
    let seed: number = 32;
    let frequency: number = 1;
    let angle_x: number = 50;
    let angle_y: number = 0;
    let angle_z: number = 0;
    let x: number = 500;
    let y: number = 400;
    let z: number = 500;
    const json = {
        terrain: {
            size: { width: 100, height: 150 }, scale: 1,
            config: {
                octaves: 6, gain: 0.35, lacunaity: 2.3, seed: 32,
                frequency: 1
            },
            rotate: { angle_x: 50, angle_y: 0, angle_z: 0 }
        },
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
    SetProjectCards,
    GetUserProjects,
    DeleteProject,
    AddProject,
    FindMyProject
};

export default ProjectService;
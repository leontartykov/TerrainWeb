import { TerrainValues } from "components/types/terrain";
import http from "http_common";

async function getParams(userName: string | null, proj_name: string | null) {
    console.log("GET_PARAMS_SERVICE");
    console.log("userName: ", userName);
    const response = await http.get('api/v1/users/' + userName + '/myProjects/' + proj_name + '/values',
        {
            headers: {
                'Authorization': sessionStorage.getItem("access_token"),
                'uuid': sessionStorage.getItem("uuid")
            }
        })
        .then((response) => {
            console.log("get_data: ", response.data);
            return {
                data: response.data
            };
        }).catch((error) => {
            console.log("status", error.response?.status);
            return {
                data: error.response?.status
            }
        })
    console.log("retur_data: ", response);
    return {
        data: response.data
    };
}

async function saveParams(userName: string | null, proj_name: any, terrain: any) {
    console.log("proj_name: ", proj_name);
    console.log("save_terrain: ", terrain);
    const response = await http.put('api/v1/users/' + userName + '/myProjects/' + proj_name, { terrain },
        {
            headers: {
                'Authorization': sessionStorage.getItem("access_token"),
                'uuid': sessionStorage.getItem("uuid")
            }
        })
        .then((response) => {
            console.log("get_data: ", response.data);
            return {
                data: response.data
            };
        })
        .catch((error) => {
            console.log("status", error.response?.status);
            return {
                data: error.response?.status
            }
        })
    console.log("retur_data: ", response);
    return {
        data: response.data
    };
}

async function getRatingProjectParams(proj_name: string | null)
{
    const response = await http.get('api/v1/valueJobs/allProjects/'+proj_name,
        {
            headers: {
                'Authorization': sessionStorage.getItem("access_token"),
                'uuid': sessionStorage.getItem("uuid")
            }
        })
        .then((response) => {
            console.log("get_data: ", response.data);
            return {
                data: response.data
            };
        }).catch((error) => {
            console.log("status", error.response?.status);
            return {
                data: error.response?.status
            }
        })
    console.log("retur_data: ", response);
    return {
        data: response.data
    };
}

const TerrainService = {
    getParams,
    saveParams,
    getRatingProjectParams
};

export default TerrainService;
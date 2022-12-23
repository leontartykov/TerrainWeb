import { TerrainValues } from "components/types/terrain";
import http from "http_common";

async function getParams(id_user: string, proj_name: string|null) {
    console.log("GET_PARAMS_SERVICE");
    const response = await http.get('api/v1/users/' + id_user + '/projects/' + proj_name + '/values').then((response) => {
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

async function saveParams(id_user: string, proj_name: any, terrain: any) {
    console.log("proj_name: ", proj_name);
    console.log("save_terrain: ", terrain);
    const response = await http.put('api/v1/users/'+id_user+'/projects/'+proj_name, {terrain}).then((response) => {
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
    saveParams
};

export default TerrainService;
import http from "http_common";

async function getParams(id_user:string, proj_name: string) {
    const response = await http.get('api/v1/users/'+id_user+'/projects/'+proj_name+'/values').then((response) => {
        return {
            data: response?.data
        };
    }).catch((error) => {
        console.log("status", error.response?.status);
        return {
            data: error.response?.status
        }
    })
    console.log("data: ", response.data);
    return {
        data: response?.data
    };
}

const TerrainService = {
    getParams
};

export default TerrainService;
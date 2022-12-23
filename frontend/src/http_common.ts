import Axios from "axios";

export default Axios.create(
    {
        baseURL: "http://localhost",
        headers:{
            'Access-Control-Allow-Methods': 'OPTIONS, POST, Get, Delete, Put, Patch',
            'Access-Control-Allow-Origin': '*',
            'Content-Type': ['application/json', 'image/png'],
            responseType: "arraybuffer",
        }
    }
)
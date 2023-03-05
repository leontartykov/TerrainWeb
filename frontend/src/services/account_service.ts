import http from "http_common";

async function Login(login: string, password: string) {
    let status: number = 0;
    const response = await http.post('api/v1/accounts/login', { login, password })
        .then(
            (response) => {
                console.log("responseLogin: ", response);
                return response;
            })
        .catch((error) => {
            return error.response;
        }
        )
    console.log("responseLogin: ", response);
    return {
        response
    };
}

async function Register(login: string, password: string, perm_level: number) {
    let status: number = 0;
    const response = await http.post('api/v1/accounts/register', { login, password, perm_level })
        .then(
            (response) => {
                return response;
            })
        .catch((error) => {
            
            return {
                status: error.response?.status,
            };
        }
        )
    return {
        status: response?.status,
    };
}

const AccountService = {
    Login,
    Register,
};

export default AccountService;
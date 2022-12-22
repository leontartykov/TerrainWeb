import http from "http_common";

async function Login(login: string, password: string)
{
    let status: number = 0;
    const response = await http.post('api/v1/accounts/login', {login, password})
        .then(
            (response) => {
                status = response.status;
                return {
                    status: response?.status,
                };
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

async function Register(login: string, password: string, perm_level: number){
    let status: number = 0;
    const response = await http.post('api/v1/accounts/register', {login, password, perm_level})
        .then(
            (response) => {
                status = response.status;
                return {
                    status: response?.status,
                };
            })
        .catch((error) => {
            let status = error.response.status;
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
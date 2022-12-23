import pageStyle from "components/pages/div_style.module.scss"
import NavBar from "components/navbar/"
import {SignInfoForm} from "components/form"
import React from "react"

import AccountService from "services/account_service"
import {Account} from "components/types/account"

export class RegistrationPage extends React.Component{
    account: Account = {login: "", password: ""}
    repeatPassword: string = "";

    setLogin(value: string){
        this.account.login = value;
    }

    setPassword(value: string){
        this.account.password = value;
    }

    setRepeatPassword(value: string){
        this.repeatPassword = value;
    }

    async handleSubmit(event: React.SyntheticEvent){  
        let data = await AccountService.Register(this.account.login, this.account.password, 2);  
        if (data.status == 201){
            window.location.href="/auth";
        }
        else{
            var component = document.getElementById("errorSign")
            if (component){
                component.innerText = "Такой пользователь уже существует!"
            }
        }
    }

    render(){
        return (
            <div className={pageStyle.div_main_page}>
                <NavBar main_menu="Ландшафт" search="Искать..." signIn_info="Войти"></NavBar>
                <SignInfoForm sign_info="Регистрация" usr_login="Имя пользователя" usr_password="Пароль" 
                            retype_password="Повторите пароль" sign_up="Зарегистрироваться"
                            onClickSignUp={this.handleSubmit.bind(this)} 
                            onChangeLogin={event => this.setLogin(event.currentTarget.value)}
                            onChangePassword={event => this.setPassword(event.currentTarget.value)}
                            onChangeRetypePassword={event => this.setRepeatPassword(event.currentTarget.value)}></SignInfoForm>
            </div>
        )
    }
}
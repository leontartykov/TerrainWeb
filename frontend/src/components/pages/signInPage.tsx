import pageStyle from "components/pages/div_style.module.scss"
import NavBar from "components/navbar/"
import {SignInfoForm} from "components/form"
import React from "react"
import AccountService from "services/account_service"
import {Account} from "components/types/account"


export class SignInPage extends React.Component {
    account: Account = {login: "", password: ""}

    setLogin(value: string){
        this.account.login = value;
    }

    setPassword(value: string){
        this.account.password = value;
    }

    async handleSubmit(event: React.SyntheticEvent){      
        let data = await AccountService.Login(this.account.login, this.account.password);
        if (data.status == 200){
            window.location.href="/auth";
            sessionStorage.setItem("usrName", this.account.login);
        }
        else{
            console.log("Incorrect login or password.");
            let component = document.getElementById("errorSign")
            if (component){
                component.innerText = "Логин или пароль не совпадают!"
            }
        }
    }

    render() {
        return (
            <div className={pageStyle.div_main_page}>
                <NavBar main_menu="Ландшафт" search="Искать..." register="Регистрация"></NavBar>
                <SignInfoForm sign_info="Вход" usr_login="Имя пользователя"
                            usr_password="Пароль" sign_in="Войти"
                            onClickSignIn={this.handleSubmit.bind(this)} 
                            onChangeLogin={event => this.setLogin(event.currentTarget.value)}
                            onChangePassword={event => this.setPassword(event.currentTarget.value)}/>
            </div>
        )   
    }
}
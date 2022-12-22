import React from 'react';
import {MainPageAuthComponent} from "components/pages/mainPageAuth"

export default class MainPageAuthService extends React.Component {
    render() { 
        let userName = sessionStorage.getItem("usrName");
        console.log("username: ", userName);
        if (userName){
            return (
            <MainPageAuthComponent usrName={userName} linkMyProjects="/auth/myProjs" 
                                     linkAllProjects="/auth/allProjs"></MainPageAuthComponent> )
        }
        return (
            <MainPageAuthComponent linkMyProjects="/auth/myProjs" 
                                     linkAllProjects="/auth/allProjs"></MainPageAuthComponent> )
    }
}
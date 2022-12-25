import React from 'react';
import {MainPageUnauthComponent} from "components/pages/mainPageUnauth"

export default class MainPageUnauthService extends React.Component {
    render() { 
        sessionStorage.removeItem("usrName");
        return (
            <MainPageUnauthComponent linkMyProjects="/signIn" 
                                     linkAllProjects="/auth/allProjs"></MainPageUnauthComponent> 
        )
    }
}
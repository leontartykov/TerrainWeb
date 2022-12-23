import React from 'react';
import {MainPageUnauthComponent} from "components/pages/mainPageUnauth"

export default class MainPageUnauthService extends React.Component {
    render() { 
        return (
            <MainPageUnauthComponent linkMyProjects="/signIn" 
                                     linkAllProjects="/auth/allProjs"></MainPageUnauthComponent> 
        )
    }
}
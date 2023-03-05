import Button from 'components/button';
import buttonStyle from "./style.module.scss"
import {Link} from "react-router-dom"

export const MyProjectsButton = (props: {img_path_my?: string, myProjsActionText: string, linkMyProjects: string}) => {
    //console.log("props.img_path: ", props.img_path);
    return (
        <div className={buttonStyle.buttonWithImg}>
            {props.img_path_my ? <img src={require("images/my_projects.png")}></img>: null} 
            <Link to={props.linkMyProjects}><Button style={buttonStyle.button} icon_style={buttonStyle.button__icon}>{props.myProjsActionText}</Button></Link>
        </div>
    )
}

export const AllProjectsButton = (props: {img_path_all?: string, allProjsActionText: string, linkAllProjects: string}) => {
        //console.log("props.img_path: ", props.img_path);
        return (
            <div className={buttonStyle.buttonWithImg}>
                {props.img_path_all ? <img src={require("images/all_projects.png")}></img>: null} 
                <Link to={props.linkAllProjects}><Button style={buttonStyle.button} icon_style={buttonStyle.button__icon}>{props.allProjsActionText}</Button></Link>
            </div>
        )
}
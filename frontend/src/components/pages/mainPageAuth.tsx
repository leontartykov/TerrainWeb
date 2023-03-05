import pageStyle from "components/pages/div_style.module.scss"
import NavBar from "components/navbar/"
import {MyProjectsButton, AllProjectsButton} from "components/button/withImage"

export const MainPageAuthComponent = (props: {linkMyProjects: string, linkAllProjects: string,
                                              usrName?: string}) =>{
    return (
        <div className={pageStyle.div_main_page}>
            <NavBar main_menu="Ландшафт" usr_name={props.usrName} search="Искать..." icon_logout="logout"></NavBar>
            <div className={pageStyle.div_type_projects}>
                <MyProjectsButton img_path_my={"images/my_projects.png"} 
                                  myProjsActionText="Мои проекты" linkMyProjects={props.linkMyProjects}></MyProjectsButton>
                <AllProjectsButton img_path_all={"images/my_projects.png"}
                                  allProjsActionText="Другие проекты" linkAllProjects={props.linkAllProjects}></AllProjectsButton>   
            </div>
        </div>
    )
}
import pageStyle from "components/pages/div_style.module.scss"
import NavBar from "components/navbar/"
import {MyProjectsButton, AllProjectsButton} from "components/button/withImage"

export const MainPageUnauthComponent = (props: {children?: React.ReactNode, linkMyProjects: string, linkAllProjects: string}) =>{
    return (
        <div className={pageStyle.div_main_page}>
            <NavBar main_menu="Ландшафт" search="Искать..." signIn_info="Войти"></NavBar>
            <div className={pageStyle.div_type_projects}>
                <MyProjectsButton img_path_my={"images/my_projects.png"} 
                                myProjsActionText="Мои проекты" linkMyProjects={props.linkMyProjects}></MyProjectsButton>
                <AllProjectsButton img_path_all={"images/all_projects.png"}
                                allProjsActionText="Другие проекты" linkAllProjects={props.linkAllProjects}></AllProjectsButton>   
            </div>
        </div>
    )
}
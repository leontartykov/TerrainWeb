import pageStyle from "components/pages/div_style.module.scss"
import cardStyle from "components/card/style.module.scss"
import NavBar from "components/navbar/"
import projectInfo from "components/types/projects"
import { ProjectCard, SearchCard, PageCard } from "components/card/index"

export const AllProjectsPage = (props: {
    userName?: string|null,
    onClickPage?: any, activePage: number, isProjects?: string, needPageCard?: string,
    project1?: projectInfo, project2?: projectInfo, project3?: projectInfo,
    onChangeSearchMyProject?: (name: any) => void,
    onKeyPressSearchMyProject?: (name: any) => void,
    onClickHandleProject1?: any, onClickHandleProject2?: any, onClickHandleProject3?: any
}) => {
    console.log("props.rate = ", props.project1);
    return (
        <div className={pageStyle.div_main_page}>
            <NavBar main_menu="Ландшафт" icon_my_projects="cottage" usr_name={props.userName} search="Искать..." icon_logout="logout" signIn_info="Войти"></NavBar>
            <div className={cardStyle.groupCard}>
                <SearchCard placeholder="Найти проект..." onChangeSearchMyProject={props.onChangeSearchMyProject} onKeyPressSearchMyProject={props.onKeyPressSearchMyProject}></SearchCard>
                {props.project1 ? <ProjectCard
                    project={props.project1.name}
                    set_rating={props.project1.rating}
                    star_icon="star"
                    user_name={props.project1.userName}
                    onClickHandleProject={props.onClickHandleProject1}></ProjectCard> : null}
                {props.project2 ? <ProjectCard
                    project={props.project2.name}
                    set_rating={props.project2.rating}
                    star_icon="star"
                    user_name={props.project2.userName}
                    onClickHandleProject={props.onClickHandleProject2}></ProjectCard> : null}
                {props.project3 ? <ProjectCard
                    project={props.project3.name}
                    set_rating={props.project3.rating}
                    star_icon="star"
                    user_name={props.project3.userName}
                    onClickHandleProject={props.onClickHandleProject3}></ProjectCard> : null}
                <PageCard cur_page={1} onClickPage={props.onClickPage}></PageCard>
            </div>
        </div>
    )
}
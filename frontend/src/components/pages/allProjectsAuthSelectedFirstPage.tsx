import pageStyle from "components/pages/div_style.module.scss"
import cardStyle from "components/card/style.module.scss"
import NavBar from "components/navbar/"
import {ProjectCard, SearchCard, PageCard} from "components/card/index"

export const AllProjectsAuthSelectedFirstPage = (props: {onClickPage?: any}) =>{
    return (
        <div className={pageStyle.div_main_page}>
            <NavBar main_menu="Ландшафт" icon_my_projects="cottage" usr_name="user_11" search="Искать..." icon_logout="logout"></NavBar>
            <div className={cardStyle.groupCard}>
                <SearchCard placeholder="Найти проект..."></SearchCard>
                <ProjectCard project="Луга" set_rating="4,3/5" star_icon="star" user_name="Night Stalker"></ProjectCard>
                <ProjectCard project="Поляна" set_rating="4,2/5" star_icon="star" user_name="czarcasm2"></ProjectCard>
                <ProjectCard project="Ландшафт" set_rating="4,7/5" star_icon="star" user_name="prozack1986"></ProjectCard>
                <PageCard cur_page={1} onClickPage={props.onClickPage}></PageCard>
            </div>
        </div>
    )
}
import pageStyle from "components/pages/div_style.module.scss"
import cardStyle from "components/card/style.module.scss"
import NavBar from "components/navbar/"
import fontstyle from "components/fonts/style.module.scss"
import {ProjectCard, SearchCard, PageCard} from "components/card/index"
import projectInfo from "components/types/projects"
import Modal, {useModal} from "components/modal/modal" 
import Button from "components/button"
import Input from "components/input"
import inputStyles from "components/input/style.module.scss"
import fontStyles from "components/fonts/style.module.scss"
import buttonStyles from "components/button/style.module.scss"
import modalStyle from "components/modal/style.module.scss"

export const MyProjectListAuthPageComponent = (props: {activePage: number, onClickPage: any, isProjects?: string
                                                        project1?: projectInfo,
                                                        project2?: projectInfo, project3?: projectInfo,
                                                        userName?: string|null, needPageCard?: string,
                                                        onChangeSearchMyProject?: (name: any) => void,
                                                        isChecked?: boolean,
                                                        onKeyPressSearchMyProject?: (name: any) => void,
                                                        onClickCheckbox?: (name: any) => void,
                                                        onClickDownload?: any, onClickDelete?: any, 
                                                        onClickAddProject?:any, onClickDeleteSelected?: any}) =>
{
    const { isOpen, toggle } = useModal();
    return (
        <>
            <Modal isOpen={isOpen} toggle={toggle}>
                <div className={modalStyle.modalBoxInner}>
                    <span className={fontStyles.middleText}>Создать проект</span>
                    <Input id="modalNewProject" style={inputStyles.createProjectModule} placeholder="Имя проекта"
                            onChange={props.onChangeSearchMyProject} onKeyPress={props.onKeyPressSearchMyProject}></Input>
                    <span className={fontStyles.littleText} id="createNewProjError"></span>
                    <Button style={buttonStyles.buttonModuleCreateProject} onClick={props.onClickAddProject}>Создать</Button>
                </div>
            </Modal>
            <div className={pageStyle.div_main_page}>
                <NavBar main_menu="Ландшафт" icon_my_projects="cottage" usr_name={props.userName} search="Искать..." icon_logout="logout"></NavBar>
                <div className={cardStyle.groupCard}>
                    <SearchCard placeholder="Найти проект..." //deleteProjIcon="delete" 
                                addProjIcon="add_box"
                                onChangeSearchMyProject={props.onChangeSearchMyProject}
                                onKeyPressSearchMyProject={props.onKeyPressSearchMyProject}
                                onClickAddProject={toggle}
                                onClickDeleteSelected={props.onClickDeleteSelected}></SearchCard>
                    {props.isProjects=="no"? <span className={fontstyle.middleText}>Нет проектов.</span>: null}
                    {props.project1 ? <ProjectCard idDel={props.project1.name} idDownload={props.project1.name} //checkbox="y" 
                                                project={props.project1.name} 
                                                set_rating={props.project1.rate ? props.project1.rate: null} 
                                                star_icon={props.project1.rate ? "star": null}
                                                id_checkbox={props.project1.name}
                                                last_edited={props.project1.last_edited}
                                                download="download" delete="delete" 
                                                onClickDownload={props.onClickDownload}
                                                onClickDelete={props.onClickDelete}
                                                isChecked={props.isChecked}
                                                onClickCheckbox={props.onClickCheckbox}
                                                ></ProjectCard>: null}
                    {props.project2 ? <ProjectCard idDel={props.project2.name} idDownload={props.project2.name} //checkbox="y"
                                                project={props.project2.name}
                                                set_rating={props.project2.rate ? props.project2.rate: null}
                                                star_icon={props.project2.rate ? "star": null}
                                                id_checkbox={props.project2.name}
                                                last_edited={props.project2.last_edited}
                                                download="download" delete="delete"
                                                onClickDownload={props.onClickDownload} onClickDelete={props.onClickDelete}
                                                isChecked={props.isChecked}
                                                onClickCheckbox={props.onClickCheckbox}></ProjectCard>: null}
                    {props.project3 ? <ProjectCard idDel={props.project3.name} idDownload={props.project3.name}// checkbox="y"
                                                project={props.project3.name}
                                                set_rating={props.project3.rate ? props.project3.rate: null}
                                                star_icon={props.project3.rate ? "star": null}
                                                id_checkbox={props.project3.name}
                                                last_edited={props.project3.last_edited}
                                                download="download" delete="delete"
                                                onClickDownload={props.onClickDownload} onClickDelete={props.onClickDelete}
                                                isChecked={props.isChecked}
                                                onClickCheckbox={props.onClickCheckbox}></ProjectCard>: null}
                    {props.needPageCard=="yes"? <PageCard cur_page={props.activePage} onClickPage={props.onClickPage}></PageCard>: null}
                </div>
                
            </div>
        </>
    )
}
import Button from 'components/button'
import Input from "components/input"
import cardStyle from 'components/card/style.module.scss'
import navbarStyle from 'components/navbar/style.module.scss'
import buttonStyle from "components/button/style.module.scss"
import fontStyle from "components/fonts/style.module.scss"
import inputStyle from "components/input/style.module.scss"
import {Link} from "react-router-dom"

export const ProjectCard = (props: {idDel?: string, idDownload?: string, 
                                    checkbox?: string, id_checkbox?: string, project?: string,
                                    set_rating?: string|null,
                                    star_icon?: string|null, last_edited?: string, user_name?: string,
                                    download?: string, delete?: string,
                                    onClickSearchMyProject?: any, onChangeSearchMyProject?: (name: any) => void,
                                    onKeyPressSearchMyProject?: (name: any) => void,
                                    onClickDelete?: any, onClickDownload?: any,
                                    onClickCheckbox?: any, isChecked?: boolean}) => {                         
    return(
        <div className={cardStyle.card}>
            <div className={navbarStyle.group}>
                {props.checkbox ? <input type="checkbox" id={props.id_checkbox} name="scales" checked={props.isChecked} onChange={props.onClickCheckbox}></input> : null}
                {props.project ? <Link to="/auth/myProjs/id"><Button style={buttonStyle.buttonCardProject} icon_style={buttonStyle.button__icon}>{props.project}</Button></Link>: null}
            </div>
            <div className={navbarStyle.group}>
                {props.set_rating ? <span className={fontStyle.middleText}>{props.set_rating}</span> : null}
                {props.star_icon ? <span className={["material-symbols-outlined", buttonStyle.button_star_icon].join(' ')}>{props.star_icon}</span>: null}
            </div>
            <div>
                {props.last_edited ? <span className={fontStyle.middleText}>{props.last_edited}</span>: null}
                {props.user_name ? <span className={fontStyle.middleText}>{props.user_name}</span>: null}
            </div>
            <div className={navbarStyle.group}>
                {props.download ? <Button id={props.idDownload} icon_style={buttonStyle.button__icon_settings}
                                          style={buttonStyle.buttonCard} icon={props.download}
                                          onClick={props.onClickDownload}></Button> : null}
                {props.delete ? <Button id={props.idDel} icon_style={buttonStyle.button__icon_settings}
                                        style={buttonStyle.buttonCard} icon={props.delete}
                                        onClick={props.onClickDelete}></Button> : null}  
            </div>
        </div>
    )
}

export const SearchCard = (props:{placeholder?: string, deleteProjIcon?: string, addProjIcon?: string,
                                  onClickAddProject?: any, onClickDeleteSelected?: any, onKeyPressSearchMyProject?: any,
                                  onChangeSearchMyProject?: any}) => {
    return (
        <div className={cardStyle.searchCard}>
            {props.placeholder ? <Input style={inputStyle.searchProject} placeholder={props.placeholder}
                                        onKeyPress={props.onKeyPressSearchMyProject} onChange={props.onChangeSearchMyProject}></Input>: null}
            {props.deleteProjIcon ? <Button icon_style={buttonStyle.button__icon_settings} style={buttonStyle.buttonProject} icon={props.deleteProjIcon}
                                            onClick={props.onClickDeleteSelected}></Button>: null}
            {props.addProjIcon ? <Button icon_style={buttonStyle.button__icon_settings} style={buttonStyle.buttonProject} icon={props.addProjIcon}
                                            onClick={props.onClickAddProject}></Button>: null}
        </div>
        )
}

export const PageCard = (props:{cur_page: number, onClickPage: any, name?: string}) => {
    const posts = [1, 2, 3, "...", 5]
    let curPage = props.cur_page;
    return (
        <div className={cardStyle.pageCard}>
            {posts.map(x=> {if(Number(x)  && x==curPage){
                                return <Button icon_style={buttonStyle.button__icon} style={buttonStyle.buttonActiveNum} onClick={props.onClickPage} name={props.name}>{x}</Button> }
                            else if(Number(x)){
                                return <Button icon_style={buttonStyle.button__icon} style={buttonStyle.buttonNum} onClick={props.onClickPage}>{x}</Button>}
                            else{
                                return <span className={fontStyle.middleText}>{x}</span>}
                            }
                        
                    )}
        </div>
    )
}
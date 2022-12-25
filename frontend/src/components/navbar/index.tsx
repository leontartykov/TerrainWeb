import Button from 'components/button'
import Input from 'components/input'
import navbarStyles from 'components/navbar/style.module.scss'
import inputStyles from 'components/input/style.module.scss';
import fontStyles from 'components/fonts/style.module.scss'
import buttonStyle from "components/button/style.module.scss"
import {Link} from "react-router-dom"

export default (props: {is_my_project?: boolean, main_menu?: string, icon_return_back?: string, icon_my_projects?: string,
                        usr_name?: string|null, search?: string, signIn_info?: string,
                        register?: string, icon_logout?: string, icon_saveProj?: string,
                        onClickSaveproj?: (name: any) => void,
                        onClickLogout?: (name: any) => void}) => {
    console.log("userName: ", props.usr_name);
    let linkLogout: string, linkMainMenu: string;
    props.icon_logout ? linkLogout = "/auth/myProjs" : linkLogout = "/SignIn";
    props.usr_name ? linkMainMenu = "/auth" : linkMainMenu = "/";

    return(
        <div className={navbarStyles.navbar}>
            <div className={navbarStyles.group}>
                {props.main_menu ? <Link to={linkMainMenu}><Button icon_style={buttonStyle.button__icon} style={buttonStyle.button}>{props.main_menu}</Button></Link> : null}
                {props.icon_return_back ? <Button icon_style={buttonStyle.button__icon} style={buttonStyle.button} icon={props.icon_return_back}></Button> : null}
                {props.icon_my_projects ? <Link to={linkLogout}><Button icon_style={buttonStyle.button__icon} style={buttonStyle.button} icon={props.icon_my_projects}></Button></Link> : null}
            </div>
            <div className={navbarStyles.group}>
                {props.icon_saveProj && props.is_my_project==true ? <Button icon_style={buttonStyle.button__icon} style={buttonStyle.button} icon={props.icon_saveProj} onClick={props.onClickSaveproj}></Button>: null}
                {props.usr_name ? <span id="usrName" className={fontStyles.middleText}>{props.usr_name}</span>: null}
                {props.search ? <Input style={inputStyles.seacrhProjectNavBar} placeholder={props.search}></Input>: null}
                {!props.usr_name && props.signIn_info? <Link to="/signIn"><Button icon_style={buttonStyle.button__icon} style={buttonStyle.button}>{props.signIn_info}</Button></Link>: null}
                {props.register ? <Link to="/registration"><Button icon_style={buttonStyle.button__icon} style={buttonStyle.button}>{props.register}</Button></Link>: null}
                {props.usr_name ? <Link to="/"><Button icon_style={buttonStyle.button__icon} style={buttonStyle.button} icon={props.icon_logout} onClick={props.onClickLogout}></Button></Link>: null}
            </div>
        </div>
    )
}
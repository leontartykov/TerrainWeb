import Button from 'components/button'
import Input from 'components/input'
import formStyles from 'components/form/style.module.scss'
import inputStyles from 'components/input/style.module.scss'
import fontStyles from 'components/fonts/style.module.scss'
import buttonStyle from "components/button/style.module.scss"
import {Link} from "react-router-dom"

export const SignInfoForm = (props: {sign_info?: string, usr_login?: string, usr_password?: string, 
                        retype_password?: string, sign_in?: string, sign_up?: string
                        onClickSignIn?: any, onClickSignUp?: any,
                        linkSignIn?: any, linkSignUp?: any,
                        onChangeLogin?: (name: any) => void,
                        onChangePassword?: (name: any) => void,
                        onChangeRetypePassword?: (name: any) => void}) => {
    return(
        <form className={formStyles.form}>
            {props.sign_info ? <span className={fontStyles.logoText}>{props.sign_info}</span> : null}
            {props.usr_login ? <Input style={inputStyles.inputUserInfo} placeholder={props.usr_login} type="login" name="login" onChange={props.onChangeLogin}></Input> : null}
            {props.usr_password ? <Input style={inputStyles.inputUserInfo} placeholder={props.usr_password} id="usrPassword" type="usrPassword" name="usrPassword" onChange={props.onChangePassword}></Input> : null}
            {props.retype_password ? <Input style={inputStyles.inputUserInfo} placeholder={props.retype_password} id="repeatUsrPassword" type="retypePassword" name="retypePassword" onChange={props.onChangeRetypePassword}></Input> : null}
            <span className={fontStyles.middleText} id="errorSign"></span>
            {props.sign_in ? <Link to={props.linkSignIn}><Button icon_style={buttonStyle.button__icon} style={buttonStyle.buttonForm} onClick={props.onClickSignIn}>{props.sign_in}</Button></Link>: null}
            {props.sign_up ? <Link to={props.linkSignUp}><Button icon_style={buttonStyle.button__icon} style={buttonStyle.buttonForm} onClick={props.onClickSignUp}>{props.sign_up}</Button></Link>: null}
        </form>
    )
}

export const CoordinatesForm = (props: {coord?: string, input?: string}) =>
{
    return(
        <div>
            {props.coord ? <span>{props.coord}</span>: null}
            {props.input ? <Input style={inputStyles.terrainCoord}></Input>: null}
        </div>
    )
}

export const TerrainForm = (props: {action?: string, width?: string, height?: string, scale?: string,
                                    octaves?: string, gain?: string, lacunarity?: string,
                                    seed?: string, frequency?: string, landscape?: string,
                                    light?: string}) => {
    return(
        <div>
            <div className={formStyles.terrainSettingsName}>
                <span className={fontStyles.middleText}>{props.action}</span>
            </div>
            <div className={formStyles.terrainSettingsForm}>
                {props.width ? <div className={formStyles.terrainFormWidth}><span>{props.width}</span><Input style={inputStyles.settings}></Input></div> : null}
                {props.height ? <div className={formStyles.terrainFormHeight}><span>{props.height}</span><Input style={inputStyles.settings}></Input></div> : null}
                {props.scale ? <div className={formStyles.terrainFormScale}><span>{props.scale}</span><Input style={inputStyles.settings}></Input></div> : null}
                {props.octaves ? <div className={formStyles.terrainFormOctaves}><span>{props.octaves}</span><Input style={inputStyles.settings}></Input></div> : null}
                {props.gain ? <div className={formStyles.terrainFormGain}><span>{props.gain}</span><Input style={inputStyles.settings}></Input></div> : null}
                {props.lacunarity ? <div className={formStyles.terrainFormLacunarity}><span>{props.lacunarity}</span><Input style={inputStyles.settings}></Input></div> : null}
                {props.seed ? <div className={formStyles.terrainFormSeed}><span>{props.seed}</span><Input style={inputStyles.settings}></Input></div> : null}
                {props.frequency ? <div className={formStyles.terrainFormFrequency}><span>{props.frequency}</span><Input style={inputStyles.settings}></Input></div> : null}
                {props.landscape ?<div>
                                    <span>{props.landscape}</span>
                                    <div className={formStyles.terrainRowCoords}>
                                        <CoordinatesForm coord="X" input="input"></CoordinatesForm>
                                        <CoordinatesForm coord="Y" input="input"></CoordinatesForm>
                                        <CoordinatesForm coord="Z" input="input"></CoordinatesForm>
                                    </div>
                                 </div>: null}
                {props.light ?<div>
                                    <span>{props.light}</span>
                                    <div className={formStyles.terrainRowCoords}>
                                        <CoordinatesForm coord="X" input="input"></CoordinatesForm>
                                        <CoordinatesForm coord="Y" input="input"></CoordinatesForm>
                                        <CoordinatesForm coord="Z" input="input"></CoordinatesForm>
                                    </div>
                                 </div>: null}
            </div>
        </div>
    )
}
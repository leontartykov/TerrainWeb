import Button from 'components/button'
import Input from 'components/input'
import formStyles from 'components/form/style.module.scss'
import inputStyles from 'components/input/style.module.scss'
import fontStyles from 'components/fonts/style.module.scss'
import buttonStyle from "components/button/style.module.scss"
import { Link } from "react-router-dom"
import { TerrainValues } from "components/types/terrain"

export const SignInfoForm = (props: {
    sign_info?: string, usr_login?: string, usr_password?: string,
    retype_password?: string, sign_in?: string, sign_up?: string
    onClickSignIn?: any, onClickSignUp?: any,
    linkSignIn?: any, linkSignUp?: any,
    onChangeLogin?: (name: any) => void,
    onChangePassword?: (name: any) => void,
    onChangeRetypePassword?: (name: any) => void
}) => {
    return (
        <form className={formStyles.form}>
            {props.sign_info ? <span className={fontStyles.logoText}>{props.sign_info}</span> : null}
            {props.usr_login ? <Input style={inputStyles.inputUserInfo} placeholder={props.usr_login} type="login" name="login" onChange={props.onChangeLogin}></Input> : null}
            {props.usr_password ? <Input style={inputStyles.inputUserInfo} placeholder={props.usr_password} id="usrPassword" type="usrPassword" name="usrPassword" onChange={props.onChangePassword}></Input> : null}
            {props.retype_password ? <Input style={inputStyles.inputUserInfo} placeholder={props.retype_password} id="repeatUsrPassword" type="retypePassword" name="retypePassword" onChange={props.onChangeRetypePassword}></Input> : null}
            <span className={fontStyles.middleText} id="errorSign"></span>
            {props.sign_in ? <Link to={props.linkSignIn}><Button icon_style={buttonStyle.button__icon} style={buttonStyle.buttonForm} onClick={props.onClickSignIn}>{props.sign_in}</Button></Link> : null}
            {props.sign_up ? <Link to={props.linkSignUp}><Button icon_style={buttonStyle.button__icon} style={buttonStyle.buttonForm} onClick={props.onClickSignUp}>{props.sign_up}</Button></Link> : null}
        </form>
    )
}

export const CoordinatesForm = (props: {
    coord?: string, input?: string, value?: number | undefined,
    onChange?: (name: any) => void
}) => {
    return (
        <div>
            {props.coord ? <span>{props.coord}</span> : null}
            {props.input ? <Input type='text' style={inputStyles.terrainCoord} value={props.value} onChange={props.onChange}></Input> : null}
        </div>
    )
}

export const TerrainForm = (props: {
    action?: string, width?: string, height?: string, scale?: string,
    octaves?: string, gain?: string, lacunarity?: string,
    seed?: string, frequency?: string, landscape?: string,
    light?: string, terVals?: any,
    onChangeTerWidth?: (name: any) => void,
    onChangeTerHeight?: (name: any) => void,
    onChangeTerScale?: (name: any) => void,
    onChangeTerFrequency?: (name: any) => void,
    onChangeTerGain?: (name: any) => void,
    onChangeTerLacunarity?: (name: any) => void,
    onChangeTerSeed?: (name: any) => void,
    onChangeTerOctaves?: (name: any) => void,
    onChangeTerRotateX?: (name: any) => void,
    onChangeTerRotateY?: (name: any) => void,
    onChangeTerRotateZ?: (name: any) => void
}) => {
    return (
        <div>
            <div className={formStyles.terrainSettingsName}>
                <span className={fontStyles.middleText}>{props.action}</span>
            </div>
            <div className={formStyles.terrainSettingsForm}>
                {props.width ? <div className={formStyles.terrainFormWidth}>
                    <span>{props.width}</span>
                    <Input type='text' style={inputStyles.settings} id="terWidth" value={props.terVals.size.width} onChange={props.onChangeTerWidth}></Input>
                </div> : null}
                {props.height ? <div className={formStyles.terrainFormHeight}>
                    <span>{props.height}</span>
                    <Input type='text' style={inputStyles.settings} id="terHeight" value={props.terVals.size.height} onChange={props.onChangeTerHeight}></Input>
                </div> : null}
                {props.scale ? <div className={formStyles.terrainFormScale}>
                    <span>{props.scale}</span>
                    <Input type='text' style={inputStyles.settings} id="terScale" value={props.terVals.scale} onChange={props.onChangeTerScale}></Input>
                </div> : null}
                {props.octaves ? <div className={formStyles.terrainFormOctaves}>
                    <span>{props.octaves}</span>
                    <Input type='text' style={inputStyles.settings} id="terOctaves" value={props.terVals.config.octaves} onChange={props.onChangeTerOctaves}></Input>
                </div> : null}
                {props.gain ? <div className={formStyles.terrainFormGain}>
                    <span>{props.gain}</span>
                    <Input type='text' style={inputStyles.settings} id="terGain" value={props.terVals.config.gain} onChange={props.onChangeTerGain}></Input>
                </div> : null}
                {props.lacunarity ? <div className={formStyles.terrainFormLacunarity}>
                    <span>{props.lacunarity}</span>
                    <Input type='text' style={inputStyles.settings} id="terLacunarity" value={props.terVals.config.lacunarity} onChange={props.onChangeTerLacunarity}></Input>
                </div> : null}
                {props.seed ? <div className={formStyles.terrainFormSeed}>
                    <span>{props.seed}</span>
                    <Input type='text' style={inputStyles.settings} id="terSeed" value={props.terVals.config.seed} onChange={props.onChangeTerSeed}></Input>
                </div> : null}
                {props.frequency ? <div className={formStyles.terrainFormFrequency}>
                    <span>{props.frequency}</span>
                    <Input type='text' style={inputStyles.settings} id="terFrequency" value={props.terVals.config.frequency} onChange={props.onChangeTerFrequency}></Input>
                </div> : null}
                {props.landscape ? <div>
                    <span>{props.landscape}</span>
                    <div className={formStyles.terrainRowCoords}>
                        <CoordinatesForm coord="X" input="input" value={props.terVals.rotate.angle_x} onChange={props.onChangeTerRotateX}></CoordinatesForm>
                        <CoordinatesForm coord="Y" input="input" value={props.terVals.rotate.angle_y} onChange={props.onChangeTerRotateY}></CoordinatesForm>
                        <CoordinatesForm coord="Z" input="input" value={props.terVals.rotate.angle_z} onChange={props.onChangeTerRotateZ}></CoordinatesForm>
                    </div>
                </div> : null}
                {props.light ? <div>
                    <span>{props.light}</span>
                    <div className={formStyles.terrainRowCoords}>
                        <CoordinatesForm coord="X" value={100} input="input"></CoordinatesForm>
                        <CoordinatesForm coord="Y" value={100} input="input"></CoordinatesForm>
                        <CoordinatesForm coord="Z" value={100} input="input"></CoordinatesForm>
                    </div>
                </div> : null}
            </div>
        </div>
    )
}
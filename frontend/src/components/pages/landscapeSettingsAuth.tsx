import pageStyle from "components/pages/div_style.module.scss"
import formStyle from "components/form/style.module.scss"
import buttonStyle from "components/button/style.module.scss"
import NavBar from "components/navbar/"
import Button from "components/button"
import {TerrainForm} from "components/form"
import {TerrainValues} from "components/types/terrain"

export const LandscapeSettingsAuthComponent = (props: {userName?: string|null, onClickGenerate?: any, 
                                image?: string, terVals?: TerrainValues}) =>{
    return (
        console.log("IMAGE_PATH"),
        <form>
            <NavBar main_menu="Ландшафт" icon_my_projects="cottage" usr_name={props.userName} search="Искать..." icon_logout="logout"></NavBar>
            <div className={formStyle.terrainSettingsUnion}>
                <div className={formStyle.formSettingBlocks}>
                    <TerrainForm action="Размеры" width="Ширина" height="Длина" scale="Масштаб" terVals={props.terVals}></TerrainForm>
                    <TerrainForm action="Преобразовать" landscape="Поворот" light="Освещение" terVals={props.terVals}></TerrainForm>
                    <TerrainForm action="Параметры" octaves="Октавы" gain="Постоянство" lacunarity="Лакунарность"
                                 seed="Зерно" frequency="Частота" terVals={props.terVals}></TerrainForm>
                </div>
                <div className={buttonStyle.buttonsGroup}>
                    <Button style={buttonStyle.buttonProject} icon_style={buttonStyle.button__icon_settings} onClick={props.onClickGenerate}>Сгенерировать</Button>
                    <Button style={buttonStyle.buttonProject} icon_style={buttonStyle.button__icon_settings} icon="download"></Button>
                </div>
            </div>
            {props.image ? <img src={`data:image/png;base64,${props.image}`}></img>: null}
        </form>
    )
}
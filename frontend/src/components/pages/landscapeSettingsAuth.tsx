import pageStyle from "components/pages/div_style.module.scss"
import formStyle from "components/form/style.module.scss"
import buttonStyle from "components/button/style.module.scss"
import NavBar from "components/navbar/"
import Button from "components/button"
import { TerrainForm } from "components/form"
import { TerrainValues } from "components/types/terrain"

export const LandscapeSettingsAuthComponent = (props: {
    userName?: string | null, onClickGenerate?: any,
    image?: string, terVals?: any,
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
    onChangeTerRotateZ?: (name: any) => void,
    onClickSaveproj?: (name: any) => void
}) => {
    console.log("IMAGE_PATH");
    console.log("image_binary: ", props.image);

    /*console.log("TER_VALS: ", props.terVals);
    if (props.terVals.data){
        terVals = props.terVals.data;}
    else{
        terVals = props.terVals;
    }*/
    return (
        <form>
            <NavBar main_menu="Ландшафт" icon_my_projects="cottage" usr_name={props.userName} search="Искать..."
                icon_logout="logout" icon_saveProj="save" onClickSaveproj={props.onClickSaveproj}></NavBar>
            <div className={formStyle.formBlockAndImage}>
                <div className={formStyle.terrainSettingsUnion}>
                    <div className={formStyle.formSettingBlocks}>
                        <TerrainForm action="Размеры" width="Ширина" height="Длина" scale="Масштаб" terVals={props.terVals}
                            onChangeTerWidth={props.onChangeTerWidth} onChangeTerHeight={props.onChangeTerHeight} onChangeTerScale={props.onChangeTerScale}></TerrainForm>
                        <TerrainForm action="Преобразовать" landscape="Поворот" light="Освещение" terVals={props.terVals}
                            onChangeTerRotateX={props.onChangeTerRotateX} onChangeTerRotateY={props.onChangeTerRotateY} onChangeTerRotateZ={props.onChangeTerRotateZ}></TerrainForm>
                        <TerrainForm action="Параметры" octaves="Октавы" gain="Постоянство" lacunarity="Лакунарность"
                            seed="Зерно" frequency="Частота" terVals={props.terVals}
                            onChangeTerOctaves={props.onChangeTerOctaves} onChangeTerLacunarity={props.onChangeTerLacunarity}
                            onChangeTerGain={props.onChangeTerGain} onChangeTerSeed={props.onChangeTerSeed} onChangeTerFrequency={props.onChangeTerFrequency}></TerrainForm>
                    </div>
                    <Button style={buttonStyle.buttonProject} icon_style={buttonStyle.button__icon_settings} onClick={props.onClickGenerate}>Сгенерировать</Button>
                </div>
                {props.image ? <img width="500" height="600" src={"data:image/png;base64," + props.image}></img> : null}
            </div>
        </form>
    )
}
export default (props: {id?: string, style?: string, icon_style?: string, text?: string,
                        children?: React.ReactNode, icon?: string, onClick?: any,name?:string,
                        onSaveProjName?: string}) => {
    return(
        <button className={props.style} onClick={props.onClick}name={props.name} id={props.id}>
            {props.icon ? <span className={["material-symbols-outlined", props.icon_style].join(' ')}>{props.icon}</span>: null }        
            {props.children}
            
        </button>
    )
}
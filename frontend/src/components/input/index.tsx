export default (props: {style?: string, placeholder?: string, id?: string, type?: string, name?: string,
                        onChange?: any, onClick?: any, value?: any, onKeyPress?: any, defaultValue?: string}) =>{
    return (
        <input className={props.style} placeholder={props.placeholder} id={props.id}
               type={props.type} name={props.name} onChange={props.onChange} onKeyDown={props.onKeyPress}
               onClick={props.onClick} defaultValue={props.value}></input>
    )
}
import React, {useState} from "react"
import modalStyle from "components/modal/style.module.scss"


interface ModalType {
    children?: React.ReactNode;
    isOpen: boolean;
    toggle: () => void;
  }

export default function Modal(props: ModalType) {
    return (
        <>
        {props.isOpen && (
            <div className={modalStyle.modal_overlay} onClick={props.toggle}>
            <div onClick={(e) => e.stopPropagation()} className={modalStyle.modal_box}>
                {props.children}
            </div>
            </div>
        )}
        </>
    );
}

export function useModal() {
    const [isOpen, setisOpen] = useState(false);
  
    const toggle = () => {
        console.log("toggle");
        setisOpen(!isOpen);
        console.log("isOpen: ", isOpen);
    };
  
    return {
      isOpen,
      toggle
    };
  }
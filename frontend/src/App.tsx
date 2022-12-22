import {Routes, Route} from "react-router-dom"

import {SignInPage} from "components/pages/signInPage"
import {RegistrationPage} from "components/pages/registrationPage"
import {AllProjectsAuthSelectedFirstPage} from "components/pages/allProjectsAuthSelectedFirstPage"
import MyProjectListAuthPageService from "services/my_project_list"
import LandscapeSettingsAuthService from "services/landscape_setting_auth_service"
import MainPageUnauth from "services/main_page_unauth"
import MainPageAuthService from "services/main_page_auth"

export default function App() {
  return(
    <Routes>
      <Route path="/" element={<MainPageUnauth/>} />
      <Route path="/signIn" element={<SignInPage/>}/>
      <Route path="/registration" element={<RegistrationPage/>}/>
      <Route path="/auth" element={<MainPageAuthService />}/>
      <Route path="/auth/allProjs" element={<AllProjectsAuthSelectedFirstPage/>}/>
      <Route path="/auth/myProjs" element={<MyProjectListAuthPageService/>}/>
      <Route path="/auth/myProjs/id" element={<LandscapeSettingsAuthService/>}/>
    </Routes>
      
  );
}
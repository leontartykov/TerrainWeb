import {Routes, Route} from "react-router-dom"

import {SignInPage} from "controllers/sign_in_page"
import {RegistrationPage} from "controllers/registration_page"
import AllProjectListService from "controllers/all_rating_project_list"
import MyProjectListAuthPageService from "controllers/my_project_list"
import LandscapeSettingsAuthService from "controllers/landscape_setting_auth_service"
import MainPageUnauth from "controllers/main_page_unauth"
import MainPageAuthService from "controllers/main_page_auth"

export default function App() {
  return(
    <Routes>
      <Route path="/" element={<MainPageUnauth/>} />
      <Route path="/signIn" element={<SignInPage/>}/>
      <Route path="/registration" element={<RegistrationPage/>}/>
      <Route path="/auth" element={<MainPageAuthService />}/>
      <Route path="/auth/allProjs" element={<AllProjectListService/>}/>
      <Route path="/auth/myProjs" element={<MyProjectListAuthPageService/>}/>
      <Route path="/auth/myProjs/id" element={<LandscapeSettingsAuthService/>} />
    </Routes>
      
  );
}
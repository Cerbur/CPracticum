#ifndef HEADER_Client
#define HEADER_Client
#define Status int
#define OK 1
#define NO 0
Status client_welcome();
Status client_user_login();
Status client_admin_login();
Status client_registered();
Status client_about_author();
Status client_exit();
#endif
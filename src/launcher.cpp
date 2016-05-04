/**
 @file   launcher.cpp
 @author Pedro Américo Toledano López
 @date   August, 2015
 @brief  Interface for managing the database and launch the game.
*/

#include <gtk/gtk.h> // Include of GTK+ Graphic Interface
#include <cstring> // Include for strcmp() function
#include <cstdlib> // Include for system() function
#include "Database.h" // Header of the Database class


/**
 Inserts the list of users in a combobox.

 @param usersCbox [out] Combobox where the users will be shown.
 @param liststore [out] Data structure where the user list is charged to be used by the combobox.

 @return Nothing
*/
void createUsersCbox(GtkWidget **usersCbox, GtkListStore **liststore)
{
	Database db1;
	User user1;
	GtkTreeIter iter;
	GtkCellRenderer *cellrenderertext;
	int tableSize = 0;
	const gchar *nameData;
	const gchar *idData;

	// Creates a list store, to store the list of users
	*liststore = gtk_list_store_new(2, G_TYPE_STRING, G_TYPE_STRING);
	// Gets the size of the table of users
	db1.getUsersTableSize(tableSize);
	// Saves all the users in the list store
	for(int row = 0; row < tableSize; row++)
	{
		db1.getNUser(row, user1);
		nameData = user1.name.c_str();
		idData = user1.id.c_str();

		gtk_list_store_append(*liststore, &iter);
		gtk_list_store_set(*liststore, &iter, 0, idData, 1, nameData, -1);
	}

	// Creates a combobox with the previous users list store
	*usersCbox = gtk_combo_box_new_with_model( GTK_TREE_MODEL(*liststore) );
	// By default, the combobox will show the first row
	gtk_combo_box_set_active( GTK_COMBO_BOX(*usersCbox), 0 );
	// Renders the first column of the combobox
	cellrenderertext = gtk_cell_renderer_text_new();
	gtk_cell_layout_pack_start( GTK_CELL_LAYOUT(*usersCbox), cellrenderertext, TRUE );
	gtk_cell_layout_set_attributes( GTK_CELL_LAYOUT(*usersCbox), cellrenderertext, "text", 0, NULL );
	// Renders the second column of the combobox
	cellrenderertext = gtk_cell_renderer_text_new();
	gtk_cell_layout_pack_start( GTK_CELL_LAYOUT(*usersCbox), cellrenderertext, TRUE );
	gtk_cell_layout_set_attributes( GTK_CELL_LAYOUT(*usersCbox), cellrenderertext, "text", 1, NULL );
}


/**
 Updates the users data of a users combobox.

 @param [out] combobox Combobox to be updated.
 @param [out] liststore Liststore for that combobox.

 @return Nothing
*/
void updateUsersCbox(GtkWidget *combobox, GtkListStore *liststore)
{
	Database db1;
	User user1;
	int tableSize = 0;
	GtkTreeIter iter;
	GtkCellRenderer *cellrenderertext;
	const gchar *nameData;
	const gchar *idData;

	// Clear the content of the list store
	gtk_list_store_clear(liststore);

	// Gets the size of the users table
	db1.getUsersTableSize(tableSize);

	// Saves all the users in the list store
	for(int row = 0; row < tableSize; row++)
	{
		db1.getNUser(row, user1);
		nameData = user1.name.c_str();
		idData = user1.id.c_str();

		gtk_list_store_append(liststore, &iter);
		gtk_list_store_set(liststore, &iter, 0, idData, 1, nameData, -1);
	}

	// Removes the renderers of the combobox
	gtk_cell_layout_clear( GTK_CELL_LAYOUT(combobox) );

	// Renders the data of the first column (id) of the users combobox
	cellrenderertext = gtk_cell_renderer_text_new();
	gtk_cell_layout_pack_start( GTK_CELL_LAYOUT(combobox), cellrenderertext, TRUE );
	gtk_cell_layout_set_attributes( GTK_CELL_LAYOUT(combobox), cellrenderertext, "text", 0, NULL );

	// Renders the data of the second column (user name) of the users combobox
	cellrenderertext = gtk_cell_renderer_text_new();
	gtk_cell_layout_pack_start( GTK_CELL_LAYOUT(combobox), cellrenderertext, TRUE );
	gtk_cell_layout_set_attributes( GTK_CELL_LAYOUT(combobox), cellrenderertext, "text", 1, NULL );

	// By default, the combobox will show the first row
	gtk_combo_box_set_active( GTK_COMBO_BOX(combobox), 0 );
}


/**
 Inserts the list of specialists in a combobox.

 @param specialistsCbox [out] Combobox where the specialists will be shown.
 @param liststore [out] Data structure where the specialists list is charged to be used by the combobox.

 @return Nothing
*/
void createSpecialistsCbox(GtkWidget **specialistsCbox, GtkListStore **liststore)
{
	Database db1;
	Specialist specialist1;
	GtkTreeIter iter;
	GtkCellRenderer *cellrenderertext;
	int tableSize = 0;
	const gchar *nameData;
	const gchar *idData;

	// Creates a list store, to store the list of specialists
	*liststore = gtk_list_store_new(2, G_TYPE_STRING, G_TYPE_STRING);
	// Gets the size of the table of specialists
	db1.getSpecialistsTableSize(tableSize);
	// Saves all the specialists in the list store
	for(int row = 0; row < tableSize; row++)
	{
		db1.getNSpecialist(row, specialist1);
		nameData = specialist1.name.c_str();
		idData = specialist1.id.c_str();

		gtk_list_store_append(*liststore, &iter);
		gtk_list_store_set(*liststore, &iter, 0, idData, 1, nameData, -1);
	}

	// Creates a combobox with the previous specialists list store
	*specialistsCbox = gtk_combo_box_new_with_model( GTK_TREE_MODEL(*liststore) );
	// By default, the combobox will show the first row
	gtk_combo_box_set_active( GTK_COMBO_BOX(*specialistsCbox), 0 );
	// Renders the first column of the combobox
	cellrenderertext = gtk_cell_renderer_text_new();
	gtk_cell_layout_pack_start( GTK_CELL_LAYOUT(*specialistsCbox), cellrenderertext, TRUE );
	gtk_cell_layout_set_attributes( GTK_CELL_LAYOUT(*specialistsCbox), cellrenderertext, "text", 0, NULL );
	// Renders the second column of the combobox
	cellrenderertext = gtk_cell_renderer_text_new();
	gtk_cell_layout_pack_start( GTK_CELL_LAYOUT(*specialistsCbox), cellrenderertext, TRUE );
	gtk_cell_layout_set_attributes( GTK_CELL_LAYOUT(*specialistsCbox), cellrenderertext, "text", 1, NULL );
}


/**
 Exports the specialist list to a *.csv file

 @param [in] widget Pointer to the widget which call this function.
 @param [in] data A gpointer that point to the data sended in the function where this function was called.

 @return Nothing.
*/
void exportSpecialistsList(GtkWidget *widget, gpointer data)
{
	GtkWidget *messageDialog;

	// Command to export the list of users
	string command = "sqlite3 -header -csv database.db 'SELECT * FROM SPECIALISTS;' > listaDeEspecialistas.csv";

	// Runs the previous command
	system(command.c_str());

	// Creates a message dialog to report about the exportation
	messageDialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "La lista de especialistas ha sido exportada correctamente.");
	// If the button of the message dialog is clicked, the message dialog will be closed
	g_signal_connect_swapped(messageDialog, "response", G_CALLBACK(gtk_widget_destroy), messageDialog);
	// Shows the message dialog
	gtk_dialog_run( GTK_DIALOG(messageDialog) );
}


/**
 Exports the users list to a *.csv file

 @param [in] widget Pointer to the widget which call this function.
 @param [in] data A gpointer that point to the data sended in the function where this function was called.

 @return Nothing.
*/
void exportUsersList(GtkWidget *widget, gpointer data)
{
	GtkWidget *messageDialog;

	// Command to export the list of users
	string command = "sqlite3 -header -csv database.db 'SELECT * FROM USERS;' > listaDeUsuarios.csv";

	// Runs the previous command
	system(command.c_str());

	// Creates a message dialog to report about the exportation
	messageDialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "La lista de usuarios ha sido exportada correctamente.");
	// If the button of the message dialog is clicked, the message dialog will be closed
	g_signal_connect_swapped(messageDialog, "response", G_CALLBACK(gtk_widget_destroy), messageDialog);
	// Shows the message dialog
	gtk_dialog_run( GTK_DIALOG(messageDialog) );
}


/**
 Exports the data of a game of a user to a *.csv file

 @param [in] widget Pointer to the widget which call this function.
 @param [in] data A gpointer that point to the data sended in the function where this function was called.

 @return Nothing.
*/
void exportGameData(GtkWidget *widget, gpointer data)
{
	GtkWidget *messageDialog;
	Database db1;
	User user1;
	Game game1;
	int posUser, posGame;

	// Gets the data sent
	GtkWidget *dialogCbox = (GtkWidget*)g_object_get_data( G_OBJECT(data), "dialogCbox" );
	GtkWidget *gamesCbox = (GtkWidget*)g_object_get_data( G_OBJECT(data), "gamesCbox" );

	// Gets the user selected in the combobox
	posUser = gtk_combo_box_get_active( GTK_COMBO_BOX(dialogCbox) );
	// Gets the game selected in the combobox
	posGame = gtk_combo_box_get_active( GTK_COMBO_BOX(gamesCbox) );

	// Gets the user data from the database
	db1.getNUser(posUser, user1);
	// Gets the game data from the database
	db1.getNGamesbyUser(user1.id, posGame, game1);

	// Command to export the game data of a game of a user
	string command = "sqlite3 -header -csv database.db 'SELECT * FROM GAME_DATA WHERE GAME_ID = "+game1.gameId+";' > datosPartida"+game1.gameId+"deUsuario"+user1.id+".csv";

	// Runs the previous command
	system(command.c_str());

	// Creates a message dialog to report about the exportation
	messageDialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Los datos de la partida han sido exportados correctamente.");
	// If the button of the message dialog is clicked, the message dialog will be closed
	g_signal_connect_swapped(messageDialog, "response", G_CALLBACK(gtk_widget_destroy), messageDialog);
	// Shows the message dialog
	gtk_dialog_run( GTK_DIALOG(messageDialog) );
}


/**
 Exports a list with all the games of a user to a *.csv file.

 @param [in] widget Pointer to the widget which call this function.
 @param [in] data A gpointer that point to the data sended in the function where this function was called.

 @return Nothing.
*/
void exportUserGames(GtkWidget *widget, gpointer dialog)
{
	GtkWidget *messageDialog;
	Database db1;
	User user1;
	int posUser;

	// Gets the data sent
	GtkWidget *dialogCbox = (GtkWidget*)g_object_get_data( G_OBJECT(dialog), "dialogCbox" );

	// Gets the user selected
	posUser = gtk_combo_box_get_active( GTK_COMBO_BOX(dialogCbox) );

	// Gets the data of the user selected
	db1.getNUser(posUser, user1);

	// Command to export the games of a user to a *.csv file
	string command = "sqlite3 -header -csv -column database.db 'SELECT * FROM GAMES WHERE USER_ID = "+user1.id+";' > partidas"+user1.id+".csv";

	// Runs the previous command
	system(command.c_str());

	// Creates a message dialog to report about the exportation
	messageDialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Las partidas del usuario han sido exportadas correctamente.");
	// If the button of the message dialog is clicked, the message dialog will be closed
	g_signal_connect_swapped(messageDialog, "response", G_CALLBACK(gtk_widget_destroy), messageDialog);
	// Shows the message dialog
	gtk_dialog_run( GTK_DIALOG(messageDialog) );
}


/**
 Add the data of a new user in the database.

 @param [in] widget Pointer to the widget which call this function.
 @param [in] data A gpointer that point to the data sended in the function where this function was called.

 @return Nothing.
*/
void addUser(GtkWidget *widget, gpointer data)
{
	GtkWidget *messageDialog;
	Database db1;
	DatabaseMessage rc;

	// Gets the data sent
	GtkWidget *idEntry = (GtkWidget*)g_object_get_data( G_OBJECT(data), "idEntry" );
	GtkWidget *nameEntry = (GtkWidget*)g_object_get_data( G_OBJECT(data), "nameEntry" );
	GtkWidget *usersCbox = (GtkWidget*)g_object_get_data( G_OBJECT(data), "usersCbox" );
	GtkListStore *liststore = (GtkListStore*)g_object_get_data( G_OBJECT(data), "liststore" );

	// Inserts the user data into the database
	rc = db1.insertUser( gtk_entry_get_text( GTK_ENTRY(idEntry) ), gtk_entry_get_text( GTK_ENTRY(nameEntry) ) );


	// Creates a message dialog of information or error, according to the answer of the database
	switch(rc)
	{
		case OK:
			messageDialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "El usuario ha sido añadido correctamente.");
			break;
		case ERROR:
			messageDialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Ya existe un usuario con esa ID.");
			break;
		case FORMAT_ERROR:
			messageDialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Por favor, completa todos los campos.");
			break;		
	}
	// If the button of the message dialog is clicked, the message dialog will be closed
	g_signal_connect_swapped(messageDialog, "response", G_CALLBACK(gtk_widget_destroy), messageDialog);
	// Shows the message dialog
	gtk_dialog_run( GTK_DIALOG(messageDialog) );


	// Updates the users combobox in the play tab to show the new user
	updateUsersCbox(usersCbox, liststore);
}


/**
 Updates the user data of an user in the database.

 @param [in] widget Pointer to the widget which call this function.
 @param [in] data A gpointer that point to the data sended in the function where this function was called.

 @return Nothing.
*/
void updateUser(GtkWidget *widget, gpointer data)
{
	GtkWidget *messageDialog;
	Database db1;
	DatabaseMessage rc = OK;
	User userDB;
	User userInserted;
	int posUser;

	// Gets the data sent
	GtkWidget *dialogCbox = (GtkWidget*)g_object_get_data( G_OBJECT(data), "dialogCbox" );
	GtkWidget *idEntry = (GtkWidget*)g_object_get_data( G_OBJECT(data), "idEntry" );
	GtkWidget *nameEntry = (GtkWidget*)g_object_get_data( G_OBJECT(data), "nameEntry" );
	GtkWidget *usersCbox = (GtkWidget*)g_object_get_data( G_OBJECT(data), "usersCbox" );
	GtkListStore *liststore = (GtkListStore*)g_object_get_data( G_OBJECT(data), "liststore" );

	// Gets the user selected
	posUser = gtk_combo_box_get_active( GTK_COMBO_BOX(dialogCbox) );

	// Gets the data of the user selected
	db1.getNUser(posUser, userDB);

	// Gets the new user data inserted in the entries
	userInserted.id = gtk_entry_get_text( GTK_ENTRY(idEntry) );
	userInserted.name = gtk_entry_get_text( GTK_ENTRY(nameEntry) );

	// Inserts the user data in the database
	if(userInserted.name != userDB.name)
		rc = db1.updateUserName(userDB.id, userInserted.name);

	if( (userInserted.id != userDB.id) && (rc == OK) )
		rc = db1.updateUserId(userDB.id, userInserted.id);

	// Creates a message dialog of information or error, according to the answer of the database
	switch(rc)
	{
		case OK:
			messageDialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Los datos han sido modificados correctamente.");
			break;
		case ERROR:
			messageDialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Ya existe un usuario con esa ID.");
			break;
		case FORMAT_ERROR:
			messageDialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Por favor, completa todos los campos.");
			break;		
	}
	// If the button of the message dialog is clicked, the message dialog will be closed
	g_signal_connect_swapped(messageDialog, "response", G_CALLBACK(gtk_widget_destroy), messageDialog);
	// Shows the message dialog
	gtk_dialog_run( GTK_DIALOG(messageDialog) );

	// Updates the users combobox in the play tab to show the new user list
	updateUsersCbox(usersCbox, liststore);
}


/**
 Deletes the user data of an user from the database.

 @param [in] widget Pointer to the widget which call this function.
 @param [in] data A gpointer that point to the data sended in the function where this function was called.

 @return Nothing.
*/
void deleteUser(GtkWidget *widget, gpointer data)
{
	GtkWidget *messageDialog;
	Database db1;
	DatabaseMessage rc;
	User user1;
	int posUser;


	// Gets the data sent
	GtkWidget *dialogCbox = (GtkWidget*)g_object_get_data( G_OBJECT(data), "dialogCbox" );
	GtkWidget *usersCbox = (GtkWidget*)g_object_get_data( G_OBJECT(data), "usersCbox" );
	GtkListStore *liststore = (GtkListStore*)g_object_get_data( G_OBJECT(data), "liststore" );

	// Gets the user selected
	posUser = gtk_combo_box_get_active( GTK_COMBO_BOX(dialogCbox) );

	// Gets the data of the user selected
	db1.getNUser(posUser, user1);

	// Deletes the user from the database
	rc = db1.deleteUser(user1.id);

	// Creates a message dialog of information or error, according to the answer of the database
	switch(rc)
	{
		case OK:
			messageDialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "El usuario ha sido eliminado correctamente.");
			break;
		case ERROR:
			messageDialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Error al intentar eliminar un usuario.");
			break;
	}
	// If the button of the message dialog is clicked, the message dialog will be closed
	g_signal_connect_swapped(messageDialog, "response", G_CALLBACK(gtk_widget_destroy), messageDialog);
	// Shows the message dialog
	gtk_dialog_run( GTK_DIALOG(messageDialog) );



	// Updates the users combobox in the play tab to show the new user list
	updateUsersCbox(usersCbox, liststore);
}


/**
 Inserts a specialist in the database checking that there are no error.

 @param [in] widget Pointer to the widget which call this function.
 @param [in] data A gpointer that point to the data sended in the function where this function was called.

 @return Nothing.
*/
void addSpecialist(GtkWidget *widget, gpointer data)
{
	GtkWidget *messageDialog;
	Database db1;
	DatabaseMessage rc;

	// Gets the data sent
	GtkWidget *idEntry = (GtkWidget*)g_object_get_data( G_OBJECT(data), "idEntry" );
	GtkWidget *nameEntry = (GtkWidget*)g_object_get_data( G_OBJECT(data), "nameEntry" );
	GtkWidget *specialtyEntry = (GtkWidget*)g_object_get_data( G_OBJECT(data), "specialtyEntry" );

	// Inserts the specialist data into the database
	rc = db1.insertSpecialist( gtk_entry_get_text( GTK_ENTRY(idEntry) ), gtk_entry_get_text( GTK_ENTRY(nameEntry) ), gtk_entry_get_text( GTK_ENTRY(specialtyEntry) ) );

	// Creates a message dialog of information or error, according to the answer of the database
	switch(rc)
	{
		case OK:
			messageDialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "El especialista ha sido añadido correctamente.");
			break;
		case ERROR:
			messageDialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Ya existe un especialista con esa ID.");
			break;
		case FORMAT_ERROR:
			messageDialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Por favor, completa todos los campos.");
			break;		
	}
	// If the button of the message dialog is clicked, the message dialog will be closed
	g_signal_connect_swapped(messageDialog, "response", G_CALLBACK(gtk_widget_destroy), messageDialog);
	// Shows the message dialog
	gtk_dialog_run( GTK_DIALOG(messageDialog) );
}


/**
 Updates the data of a specialist in the database.

 @param [in] widget Pointer to the widget which call this function.
 @param [in] data A gpointer that point to the data sended in the function where this function was called.

 @return Nothing.
*/
void updateSpecialist(GtkWidget *widget, gpointer data)
{
	GtkWidget *messageDialog;
	Database db1;
	DatabaseMessage rc = OK;
	Specialist specialistDB;
	Specialist specialistInserted;
	int posSpecialist;

	// Gets the data sent
	GtkWidget *dialogCbox = (GtkWidget*)g_object_get_data( G_OBJECT(data), "dialogCbox" );
	GtkWidget *idEntry = (GtkWidget*)g_object_get_data( G_OBJECT(data), "idEntry" );
	GtkWidget *nameEntry = (GtkWidget*)g_object_get_data( G_OBJECT(data), "nameEntry" );
	GtkWidget *specialtyEntry = (GtkWidget*)g_object_get_data( G_OBJECT(data), "specialtyEntry" );

	// Gets the specialist selected
	posSpecialist = gtk_combo_box_get_active( GTK_COMBO_BOX(dialogCbox) );

	// Gets the data of the specialist selected
	db1.getNSpecialist(posSpecialist, specialistDB);

	// Gets the new specialist data inserted in the entries
	specialistInserted.id = gtk_entry_get_text( GTK_ENTRY(idEntry) );
	specialistInserted.name = gtk_entry_get_text( GTK_ENTRY(nameEntry) );
	specialistInserted.specialty = gtk_entry_get_text( GTK_ENTRY(specialtyEntry) );

	// Inserts the new data in the database
	if(specialistInserted.name != specialistDB.name)
		rc = db1.updateSpecialistName(specialistDB.id, specialistInserted.name);

	if( (specialistInserted.specialty != specialistDB.specialty) && (rc == OK) )
		rc = db1.updateSpecialistSpecialty(specialistDB.id, specialistInserted.specialty);

	if( (specialistInserted.id != specialistDB.id) && (rc == OK) )
		rc = db1.updateSpecialistId(specialistDB.id, specialistInserted.id);


	// Creates a message dialog of information or error, according to the answer of the database
	switch(rc)
	{
		case OK:
			messageDialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Los datos han sido modificados correctamente.");
			break;
		case ERROR:
			messageDialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Ya existe un especialista con esa ID.");
			break;
		case FORMAT_ERROR:
			messageDialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Por favor, completa todos los campos.");
			break;		
	}
	// If the button of the message dialog is clicked, the message dialog will be closed
	g_signal_connect_swapped(messageDialog, "response", G_CALLBACK(gtk_widget_destroy), messageDialog);
	// Shows the message dialog
	gtk_dialog_run( GTK_DIALOG(messageDialog) );
}


/**
 Deletes the data of a specialist from the database.

 @param [in] widget Pointer to the widget which call this function.
 @param [in] data A gpointer that point to the data sended in the function where this function was called.

 @return Nothing.
*/
void deleteSpecialist(GtkWidget *widget, gpointer data)
{
	GtkWidget *messageDialog;
	Database db1;
	DatabaseMessage rc;
	Specialist specialist1;
	int posSpecialist;


	// Gets the data sent
	GtkWidget *dialogCbox = (GtkWidget*)g_object_get_data( G_OBJECT(data), "dialogCbox" );

	// Gets the specialist selected
	posSpecialist = gtk_combo_box_get_active( GTK_COMBO_BOX(dialogCbox) );

	// Gets the data of the specialist selected
	db1.getNSpecialist(posSpecialist, specialist1);

	// Deletes the specialist from the database
	rc = db1.deleteSpecialist(specialist1.id);

	// Creates a message dialog of information or error, according to the answer of the database
	switch(rc)
	{
		case OK:
			messageDialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "El especialista ha sido eliminado correctamente.");
			break;
		case ERROR:
			messageDialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Error al intentar eliminar un especialista.");
			break;
	}
	// If the button of the message dialog is clicked, the message dialog will be closed
	g_signal_connect_swapped(messageDialog, "response", G_CALLBACK(gtk_widget_destroy), messageDialog);
	// Shows the message dialog
	gtk_dialog_run( GTK_DIALOG(messageDialog) );
}


/**
 Saves in the database a link between a user and a specialist.

 @param [in] widget Pointer to the widget which call this function.
 @param [in] data A gpointer that point to the data sended in the function where this function was called.

 @return Nothing.
*/
void linkUserSpecialist(GtkWidget *widget, gpointer data)
{
	GtkWidget *messageDialog;
	Database db1;
	DatabaseMessage rc;
	User user1;
	Specialist specialist1;
	int posUser, posSpecialist;

	// Gets the data sent
	GtkWidget *usersDialogCbox = (GtkWidget*)g_object_get_data( G_OBJECT(data), "usersDialogCbox" );
	GtkWidget *specialistDialogCbox = (GtkWidget*)g_object_get_data( G_OBJECT(data), "specialistDialogCbox" );

	// Gets the user selected
	posUser = gtk_combo_box_get_active( GTK_COMBO_BOX(usersDialogCbox) );
	// Gets the data of the user selected
	db1.getNUser(posUser, user1);

	// Gets the specialist selected
	posSpecialist = gtk_combo_box_get_active( GTK_COMBO_BOX(specialistDialogCbox) );
	// Gets the data of the specialist selected
	db1.getNSpecialist(posSpecialist, specialist1);

	// Links an user and a specialist in the database
	rc = db1.insertLinkUserSpecialist(user1.id, specialist1.id);

	// Creates a message dialog of information or error, according to the answer of the database
	switch(rc)
	{
		case OK:
			messageDialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Usuario y especialista han sido vinculados.");
			break;
		case ERROR:
			messageDialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Usuario y especialista ya estaban vinculados. No se hizo nada.");
			break;
	}
	// If the button of the message dialog is clicked, the message dialog will be closed
	g_signal_connect_swapped(messageDialog, "response", G_CALLBACK(gtk_widget_destroy), messageDialog);
	// Shows the message dialog
	gtk_dialog_run( GTK_DIALOG(messageDialog) );
}


/**
 Deletes from the database a link between a user and a specialist.

 @param [in] widget Pointer to the widget which call this function.
 @param [in] data A gpointer that point to the data sended in the function where this function was called.

 @return Nothing.
*/
void unlinkUserSpecialist(GtkWidget *widget, gpointer data)
{
	GtkWidget *messageDialog;
	Database db1;
	DatabaseMessage rc;
	User user1;
	Specialist specialist1;
	int posUser, posSpecialist;

	// Gets the data sent
	GtkWidget *usersDialogCbox = (GtkWidget*)g_object_get_data( G_OBJECT(data), "usersDialogCbox" );
	GtkWidget *specialistDialogCbox = (GtkWidget*)g_object_get_data( G_OBJECT(data), "specialistDialogCbox" );

	// Gets the user selected
	posUser = gtk_combo_box_get_active( GTK_COMBO_BOX(usersDialogCbox) );
	// Gets the data of the user selected
	db1.getNUser(posUser, user1);

	// Gets the specialist selected
	posSpecialist = gtk_combo_box_get_active( GTK_COMBO_BOX(specialistDialogCbox) );
	// Gets the data of the specialist selected
	db1.getNSpecialist(posSpecialist, specialist1);

	// Links an user and a specialist in the database
	rc = db1.deleteLinkUserSpecialist(user1.id, specialist1.id);

	// Creates a message dialog of information or error, according to the answer of the database
	switch(rc)
	{
		case OK:
			messageDialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Usuario y especialista han sido desvinculados.");
			break;
		case ERROR:
			messageDialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Usuario y especialista no estaban vinculados. No se hizo nada.");
			break;
	}
	// If the button of the message dialog is clicked, the message dialog will be closed
	g_signal_connect_swapped(messageDialog, "response", G_CALLBACK(gtk_widget_destroy), messageDialog);
	// Shows the message dialog
	gtk_dialog_run( GTK_DIALOG(messageDialog) );
}


/**
 Checks if the data enter in an entry in the game settings is valid (is a number in the right range).

 @param [in] string String to be checked.
 @param [in] bottom Minimum value of the range.
 @param [in] top Maximum value of the range
*/
bool entryIsValid(const char *string, int bottom, int top)
{
	istringstream iss( string );
	int numConvert;
	iss >> numConvert;

	if ( !numConvert )
		return false;
	else if(numConvert < bottom || numConvert > top)
		return false;
	else
		return true;
}


/**
 Runs the game with the parameters set in the game settings.

 @param [in] widget Pointer to the widget which call this function.
 @param [in] data A gpointer that point to the data sended in the function where this function was called.

 @return Nothing.
*/
void runGame(GtkWidget *widget, gpointer data)
{
	GtkWidget *messageDialog;
	Database db1;
	User user1;
	string command;

	// Gets the data sent
	GtkWidget *fruitDurationEntry = (GtkWidget*)g_object_get_data( G_OBJECT(data), "fruitDurationEntry" );
	GtkWidget *gameDurationEntry = (GtkWidget*)g_object_get_data( G_OBJECT(data), "gameDurationEntry" );
	GtkWidget *usersCbox = (GtkWidget*)g_object_get_data( G_OBJECT(data), "usersCbox" );

	// Gets the input text from the entries
	const gchar *fruitDuration = gtk_entry_get_text( GTK_ENTRY(fruitDurationEntry) );
	const gchar *gameDuration = gtk_entry_get_text( GTK_ENTRY(gameDurationEntry) );

	// Gets the combobox row selected
	int posUser = gtk_combo_box_get_active( GTK_COMBO_BOX(usersCbox) );

	// Gets the data of the user selected
	db1.getNUser(posUser, user1);

	// Command to run the game
	command = "./bin/game "+string(fruitDuration)+" "+string(gameDuration)+" "+user1.id;


	if( !entryIsValid(gameDuration, 10, 3540) )
	{
		// Creates a message dialog of error
		messageDialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "El dato introducido como duración del juego es incorrecto o está fuera del rango permitido (entre 10 y 3540 segundos).");
		// If the button of the message dialog is clicked, the message dialog will be closed
		g_signal_connect_swapped(messageDialog, "response", G_CALLBACK(gtk_widget_destroy), messageDialog);
		// Shows the message dialog
		gtk_dialog_run( GTK_DIALOG(messageDialog) );
	}
	else if( !entryIsValid(fruitDuration, 1, 60) )
	{
		// Creates a message dialog of error
		messageDialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "El dato introducido como duración de la fruta es incorrecto o está fuera del rango permitido (entre 1 y 60 segundos).");
		// If the button of the message dialog is clicked, the message dialog will be closed
		g_signal_connect_swapped(messageDialog, "response", G_CALLBACK(gtk_widget_destroy), messageDialog);
		// Shows the message dialog
		gtk_dialog_run( GTK_DIALOG(messageDialog) );
	}
	else
	{
		// Runs the command to run the game
		system( command.c_str() );
	}
}


/**
 Runs the keyboard.

 @param [in] widget Pointer to the widget which call this function.
 @param [in] data A gpointer that point to the data sended in the function where this function was called.

 @return Nothing.
*/
void runKeyboard(GtkWidget *widget, gpointer data)
{
	string command;
	stringstream table, comm;
	int *keyboardOptions = (int*)data;

	table << keyboardOptions[0];
	comm << keyboardOptions[1];

	// Command to run the game
	command = "./bin/keyboard " + table.str() + " " + comm.str();

	// Runs the command to run the game
	system( command.c_str() );
}


/**
 Shows a dialog where the user can choose which game want to export.

 @param [in] widget Pointer to the widget which call this function.
 @param [in] data A gpointer that point to the data sended in the function where this function was called.

 @return Nothing.
*/
void exportGameDataDialog(GtkWidget *widget, gpointer data)
{
	GtkWidget *dialog;
	GtkWidget *vbox;
	GtkWidget *grid;
	GtkWidget *gamesCbox;
	GtkWidget *button;
	GtkListStore *liststore;
	GtkTreeIter iter;
	GtkCellRenderer *cellrenderertext;
	GtkWidget *label;

	Database db1;
	User user;
	Game game;
	int posUser;
	int gamesNum = 0;
	const gchar *dateData;


	// Gets the data sent
	GtkWidget *dialogCbox = (GtkWidget*)g_object_get_data( G_OBJECT(data), "dialogCbox" );

	// Creates the dialog box
	dialog = gtk_dialog_new();
	// Sets the title of the dialog
	gtk_window_set_title( GTK_WINDOW(dialog), "Exportar datos de una partida" );

	// Gets the user selected in the combobox
	posUser = gtk_combo_box_get_active( GTK_COMBO_BOX(dialogCbox) );

	// Gets the user data from the database
	db1.getNUser(posUser, user);



	// Creates a list store, to store the list of games
	liststore = gtk_list_store_new(2, G_TYPE_STRING, G_TYPE_STRING);
	// Gets the number of games that this user has played
	db1.getUserGamesNum(user.id, gamesNum);
	// Saves all the games of the user in the list store
	for(int row = 0; row < gamesNum; row++)
	{
		db1.getNGamesbyUser(user.id, row, game);
		dateData = game.date.c_str();

		gtk_list_store_append(liststore, &iter);
		gtk_list_store_set(liststore, &iter, 0, dateData, /*1, nameData,*/ -1);
	}

	// Creates a combobox with the previous users list store
	gamesCbox = gtk_combo_box_new_with_model( GTK_TREE_MODEL(liststore) );
	// By default, the combobox will show the first row
	gtk_combo_box_set_active( GTK_COMBO_BOX(gamesCbox), 0 );

	// Renders the first column of the combobox
	cellrenderertext = gtk_cell_renderer_text_new();
	gtk_cell_layout_pack_start( GTK_CELL_LAYOUT(gamesCbox), cellrenderertext, TRUE );
	gtk_cell_layout_set_attributes( GTK_CELL_LAYOUT(gamesCbox), cellrenderertext, "text", 0, NULL );
	// Renders the second column of the combobox
	cellrenderertext = gtk_cell_renderer_text_new();
	gtk_cell_layout_pack_start( GTK_CELL_LAYOUT(gamesCbox), cellrenderertext, TRUE );
	gtk_cell_layout_set_attributes( GTK_CELL_LAYOUT(gamesCbox), cellrenderertext, "text", 1, NULL );

	// Creates a label to explain the games combobox
	label = gtk_label_new("Elige la partida:");


	// Creates a container of widgets
	grid = gtk_grid_new();
	// Inserts the widgets in that container
	gtk_grid_attach( GTK_GRID(grid), label, 0, 0, 1, 1 );
	gtk_grid_attach( GTK_GRID(grid), gamesCbox, 1, 0, 1, 1 );

	// Creates a vertical box container, contained inside of the dialog
	vbox = gtk_dialog_get_content_area( GTK_DIALOG(dialog) );
	// Inserts the grid into the vertical box
	gtk_box_pack_start((GtkBox*)vbox, grid, FALSE, FALSE, 1);


	// Data to be sent to the callback function
	g_object_set_data( G_OBJECT(dialog), "dialogCbox", dialogCbox );
	g_object_set_data( G_OBJECT(dialog), "gamesCbox", gamesCbox );


	// Creates an action button
 	button = gtk_button_new_with_label("Exportar");
	// Calls a callback function when the button is clicked
	g_signal_connect(button, "clicked", G_CALLBACK(exportGameData), dialog);
	// Adds the button to the dialog
	gtk_dialog_add_action_widget( GTK_DIALOG(dialog), button, GTK_RESPONSE_APPLY );

	// Adds a cancel button
	gtk_dialog_add_button( GTK_DIALOG(dialog), "Cancelar", GTK_RESPONSE_CANCEL );


	// Shows all the widget in the dialog
	gtk_widget_show_all(dialog);
	// Blocks in a recursive loop until the dialog either emits the 'response' signal, or is destroyed
	gtk_dialog_run( GTK_DIALOG(dialog) );
	// Destroys the dialog
	gtk_widget_destroy(dialog);
}


/**
 Shows a dialog to enter the data of a new user.

 @param [in] widget Pointer to the widget which call this function.
 @param [in] data A gpointer that point to the data sended in the function where this function was called.

 @return Nothing.
*/
void addUserDialog(GtkWidget *widget, gpointer data)
{
	GtkWidget *dialog;
	GtkWidget *idLabel, *nameLabel;
	GtkWidget *idEntry, *nameEntry;
	GtkWidget *grid;
	GtkWidget *vbox;
	GtkWidget *addButton;
	GtkWidget *keyboardButton;
	int keyboardOptions[2] = {1, 1};

	// Gets the data sent
	GtkWidget *usersCbox = (GtkWidget*)g_object_get_data( G_OBJECT(data), "usersCbox" );
	GtkListStore *liststore = (GtkListStore*)g_object_get_data( G_OBJECT(data), "liststore" );

	// Creates the dialog box
	dialog = gtk_dialog_new();
	// Sets the title for the dialog
	gtk_window_set_title( GTK_WINDOW(dialog), "Añadir un nuevo usuario" );

	// Creates the entry to input the identification number (id) of the user
	idEntry = gtk_entry_new();
	// Creates the entry to input the user name
	nameEntry = gtk_entry_new();
	// Creates a label to explain the id entry
	idLabel = gtk_label_new("Número identificativo:");
	// Creates a label to explain the user name entry
	nameLabel = gtk_label_new("Nombre completo:");

	// Creates a container of widgets
	grid = gtk_grid_new();
	// Inserts the widgets in that container
	gtk_grid_attach( GTK_GRID(grid), idLabel, 0, 0, 1, 1 );
	gtk_grid_attach( GTK_GRID(grid), idEntry, 1, 0, 1, 1 );
	gtk_grid_attach( GTK_GRID(grid), nameLabel, 0, 1, 1, 1 );
	gtk_grid_attach( GTK_GRID(grid), nameEntry, 1, 1, 1, 1 );

	// Creates a vertical box container, contained inside of the dialog
	vbox = gtk_dialog_get_content_area( GTK_DIALOG(dialog) );
	// Inserts the grid into the vertical box
	gtk_box_pack_start( GTK_BOX(vbox), grid, FALSE, FALSE, 1 );


	// Data to be sent to the callback function
	g_object_set_data( G_OBJECT(dialog), "idEntry", idEntry );
	g_object_set_data( G_OBJECT(dialog), "nameEntry", nameEntry );
	g_object_set_data( G_OBJECT(dialog), "usersCbox", usersCbox );
	g_object_set_data( G_OBJECT(dialog), "liststore", liststore );


	// Creates the keyboard button
 	keyboardButton = gtk_button_new_with_label("Teclado virtual");
	// Calls a callback function when the keyboard button is clicked
	g_signal_connect(keyboardButton, "clicked", G_CALLBACK(runKeyboard), keyboardOptions);
	// Adds the keyboard button to the dialog
	gtk_dialog_add_action_widget( GTK_DIALOG(dialog), keyboardButton, GTK_RESPONSE_APPLY );

	// Creates the add button
 	addButton = gtk_button_new_with_label("Añadir");
	// Calls a callback function when the add button is clicked
	g_signal_connect(addButton, "clicked", G_CALLBACK(addUser), dialog);
	// Adds the add button to the dialog
	gtk_dialog_add_action_widget( GTK_DIALOG(dialog), addButton, GTK_RESPONSE_APPLY );

	// Adds a cancel button
	gtk_dialog_add_button( GTK_DIALOG(dialog), "Cancelar", GTK_RESPONSE_CANCEL );


	// Shows all the widget in the dialog
	gtk_widget_show_all(dialog);

	// Blocks in a recursive loop until the dialog either emits the 'response' signal, or is destroyed
	gtk_dialog_run( GTK_DIALOG(dialog) );
	
	// Updates the users combobox in the play tab to show the new user
	updateUsersCbox(usersCbox, liststore);

	// Destroys the dialog
	gtk_widget_destroy(dialog);
}


/**
 Shows a dialog where the user can enter the new data of a user.

 @param [in] widget Pointer to the widget which call this function.
 @param [in] data A gpointer that point to the data sended in the function where this function was called.

 @return Nothing.
*/
void updateUserDialog(GtkWidget *widget, gpointer data)
{
	GtkWidget *dialog;
	GtkWidget *idLabel, *nameLabel;
	GtkWidget *idEntry, *nameEntry;
	GtkWidget *updateButton;
	GtkWidget *vbox, *hbox1, *hbox2;
	GtkWidget *grid;
	Database db1;
	User user1;
	int posUser;


	// Gets the data sent
	GtkWidget *dialogCbox = (GtkWidget*)g_object_get_data( G_OBJECT(data), "dialogCbox" );
	GtkWidget *usersCbox = (GtkWidget*)g_object_get_data( G_OBJECT(data), "usersCbox" );
	GtkListStore *liststore = (GtkListStore*)g_object_get_data( G_OBJECT(data), "liststore" );

	// Creates the dialog box
	dialog = gtk_dialog_new();
	// Sets the title of the dialog
	gtk_window_set_title( GTK_WINDOW(dialog), "Modificar usuario" );

	// Gets the user selected in the combobox
	posUser = gtk_combo_box_get_active( GTK_COMBO_BOX(dialogCbox) );

	// Gets the user data from the database
	db1.getNUser(posUser, user1);


	// Creates a entry to input the identification number (id) of the user
	idEntry = gtk_entry_new();
	// Sets the value by default
	gtk_entry_set_text( GTK_ENTRY(idEntry), user1.id.c_str() );

	// Creates a entry to input the user name
	nameEntry = gtk_entry_new();
	// Sets the value by default
	gtk_entry_set_text( GTK_ENTRY(nameEntry), user1.name.c_str() );


	// Creates a label to explain the id entry
	idLabel = gtk_label_new("Número identificativo:");
	// Creates a label to explain the name entry
	nameLabel = gtk_label_new("Nombre completo:");


	// Creates a container of widgets
	grid = gtk_grid_new();
	// Inserts the widgets in that container
	gtk_grid_attach( GTK_GRID(grid), idLabel, 0, 0, 1, 1 );
	gtk_grid_attach( GTK_GRID(grid), idEntry, 1, 0, 1, 1 );
	gtk_grid_attach( GTK_GRID(grid), nameLabel, 0, 1, 1, 1 );
	gtk_grid_attach( GTK_GRID(grid), nameEntry, 1, 1, 1, 1 );

	// Creates a vertical box container, contained inside of the dialog
	vbox = gtk_dialog_get_content_area( GTK_DIALOG(dialog) );
	// Inserts the grid into the vertical box
	gtk_box_pack_start( GTK_BOX(vbox), grid, FALSE, FALSE, 1 );


	// Data to be sent to the callback function
	g_object_set_data( G_OBJECT(dialog), "idEntry", idEntry );
	g_object_set_data( G_OBJECT(dialog), "nameEntry", nameEntry );
	g_object_set_data( G_OBJECT(dialog), "dialogCbox", dialogCbox );
	g_object_set_data( G_OBJECT(dialog), "usersCbox", usersCbox );
	g_object_set_data( G_OBJECT(dialog), "liststore", liststore );


	// Creates the update button
 	updateButton = gtk_button_new_with_label("Modificar");
	// Calls a callback function when the add button is clicked
	g_signal_connect(updateButton, "clicked", G_CALLBACK(updateUser), dialog);
	// Adds the action button to the dialog
	gtk_dialog_add_action_widget( GTK_DIALOG(dialog), updateButton, GTK_RESPONSE_APPLY );

	// Adds a cancel button
	gtk_dialog_add_button( GTK_DIALOG(dialog), "Cancelar", GTK_RESPONSE_CANCEL );


	// Shows all the widget in the dialog
	gtk_widget_show_all(dialog);
	// Blocks in a recursive loop until the dialog either emits the 'response' signal, or is destroyed
	gtk_dialog_run( GTK_DIALOG(dialog) );
	// Destroys the dialog
	gtk_widget_destroy(dialog);
}


/**
 Shows a dialog where the user can enter the new data of a user.

 @param [in] widget Pointer to the widget which call this function.
 @param [in] data A gpointer that point to the data sended in the function where this function was called.

 @return Nothing.
*/
void chooseUserDialog(GtkWidget *widget, gpointer data)
{
	GtkWidget *dialog;
	GtkWidget *label;
	GtkWidget *dialogCbox;
	GtkWidget *grid;
	GtkWidget *vbox;
	GtkWidget *button;
	GtkListStore *dialogListstore;

	Database db1;
	const gchar *nameData;
	const gchar *idData;


	// Creates the dialog box
	dialog = gtk_dialog_new();
	// Sets the title of the dialog
	if( strcmp( gtk_button_get_label( GTK_BUTTON(widget) ), "Eliminar usuario") == 0 )
		gtk_window_set_title( GTK_WINDOW(dialog), "Eliminar usuario" );
	else if( strcmp( gtk_button_get_label( GTK_BUTTON(widget) ), "Modificar usuario") == 0 )
		gtk_window_set_title( GTK_WINDOW(dialog), "Modificar usuario" );
	else if( strcmp( gtk_button_get_label( GTK_BUTTON(widget) ), "Partidas de un usuario") == 0 )
		gtk_window_set_title( GTK_WINDOW(dialog), "Exportar partidas" );
	else if( strcmp( gtk_button_get_label( GTK_BUTTON(widget) ), "Datos de una partida") == 0 )
		gtk_window_set_title( GTK_WINDOW(dialog), "Exportar datos de una partida" );


	// Gets the data sent
	GtkWidget *usersCbox = (GtkWidget*)g_object_get_data( G_OBJECT(data), "usersCbox" );
	GtkListStore *liststore = (GtkListStore*)g_object_get_data( G_OBJECT(data), "liststore" );


	// Creates the users combobox
	createUsersCbox(&dialogCbox, &dialogListstore);

	// Creates a label to explain the users combobox
	label = gtk_label_new("Elige el usuario:");


	// Creates a container of widgets
	grid = gtk_grid_new();
	// Inserts the widgets in that container
	gtk_grid_attach( GTK_GRID(grid), label, 0, 0, 1, 1 );
	gtk_grid_attach( GTK_GRID(grid), dialogCbox, 1, 0, 1, 1 );

	// Creates a vertical box container, contained inside of the dialog
	vbox = gtk_dialog_get_content_area( GTK_DIALOG(dialog) );
	// Inserts the grid into the vertical box
	gtk_box_pack_start( GTK_BOX(vbox), grid, FALSE, FALSE, 1 );

	
	// Data to be sent to the callback function
	g_object_set_data( G_OBJECT(dialog), "dialogCbox", dialogCbox );
	g_object_set_data( G_OBJECT(dialog), "usersCbox", usersCbox );
	g_object_set_data( G_OBJECT(dialog), "liststore", liststore );

	if( strcmp( gtk_button_get_label( GTK_BUTTON(widget) ), "Eliminar usuario") == 0 )
	{
		// Creates the delete button
	 	button = gtk_button_new_with_label("Eliminar");
		// Calls a callback function when the delete button is clicked
		g_signal_connect(button, "clicked", G_CALLBACK(deleteUser), dialog);
	}
	else if( strcmp( gtk_button_get_label( GTK_BUTTON(widget) ), "Modificar usuario") == 0 )
	{
		// Creates the update button
	 	button = gtk_button_new_with_label("Modificar");
		// Calls a callback function when the update button is clicked
		g_signal_connect(button, "clicked", G_CALLBACK(updateUserDialog), dialog);
	}
	else if( strcmp( gtk_button_get_label( GTK_BUTTON(widget) ), "Partidas de un usuario") == 0 )
	{
		// Creates the update button
	 	button = gtk_button_new_with_label("Exportar");
		// Calls a callback function when the update button is clicked
		g_signal_connect(button, "clicked", G_CALLBACK(exportUserGames), dialog);
	}
	else if( strcmp( gtk_button_get_label( GTK_BUTTON(widget) ), "Datos de una partida") == 0 )
	{
		// Creates the update button
	 	button = gtk_button_new_with_label("Siguiente");
		// Calls a callback function when the update button is clicked
		g_signal_connect(button, "clicked", G_CALLBACK(exportGameDataDialog), dialog);
	}
	// Adds the action button to the dialog
	gtk_dialog_add_action_widget( GTK_DIALOG(dialog), button, GTK_RESPONSE_APPLY );
	// Adds a cancel button
	gtk_dialog_add_button( GTK_DIALOG(dialog), "Cancelar", GTK_RESPONSE_CANCEL );


	// Shows all the widget in the dialog
	gtk_widget_show_all(dialog);
	// Blocks in a recursive loop until the dialog either emits the 'response' signal, or is destroyed
	gtk_dialog_run( GTK_DIALOG(dialog) );
	// Destroys the dialog
	gtk_widget_destroy(dialog);
}


/**
 Shows a dialog to show the list of users.

 @param [in] widget Pointer to the widget which call this function.
 @param [in] data A gpointer that point to the data sended in the function where this function was called.

 @return Nothing.
*/
void usersListDialog(GtkWidget *widget, gpointer data)
{
	GtkWidget *dialog;
	GtkWidget *vbox;
	GtkWidget *treeView;
	GtkListStore *liststore;
	GtkTreeIter iter;
	GtkTreeViewColumn *col;
	GtkCellRenderer *renderer;
	Database db1;
	User user1;
	int tableSize = 0;
	const gchar *nameData, *idData;

	
	// Creates a new dialog
	dialog = gtk_dialog_new();
	// Sets the size of the dialog
	gtk_window_set_default_size( GTK_WINDOW(dialog), 400, 300 );
	// Sets the name of the dialog
	gtk_window_set_title( GTK_WINDOW(dialog), "Lista de usuarios" );
	// Gets the content area of the dialog
	vbox = gtk_dialog_get_content_area( GTK_DIALOG(dialog) );

	// Creates a list store, to store the list of users
	liststore = gtk_list_store_new(4, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT);
	// Gets the size of the table of users
	db1.getUsersTableSize(tableSize);
	// Saves all the users in the list store
	for(int row = 0; row < tableSize; row++)
	{
		db1.getNUser(row, user1);
		nameData = user1.name.c_str();
		idData = user1.id.c_str();

		gtk_list_store_append(liststore, &iter);
		gtk_list_store_set(liststore, &iter, 0, idData, 1, nameData, 2, user1.successes, 3, user1.failures, -1);
	}

	// Creates a tree view with the previous list store
	treeView = gtk_tree_view_new_with_model( GTK_TREE_MODEL(liststore) );
	// Inserts the tree view in the dialog
	gtk_box_pack_start( GTK_BOX(vbox), treeView, FALSE, FALSE, 1 );

	
	// Creates a new column for the tree view
	col = gtk_tree_view_column_new();
	// Sets the name of the column
	gtk_tree_view_column_set_title(col, "ID");
	// Renders the column
	renderer = gtk_cell_renderer_text_new();
	gtk_tree_view_column_pack_start(GTK_TREE_VIEW_COLUMN(col), renderer, FALSE);
	gtk_tree_view_column_set_attributes(GTK_TREE_VIEW_COLUMN(col), renderer, "text", 0, NULL);
	// Adds the column to the tree view
	gtk_tree_view_append_column( GTK_TREE_VIEW(treeView), col );


	// Creates a new column for the tree view
	col = gtk_tree_view_column_new();
	// Sets the name of the column
	gtk_tree_view_column_set_title(col, "Nombre");
	// Renders the column
	renderer = gtk_cell_renderer_text_new();
	gtk_tree_view_column_pack_start(GTK_TREE_VIEW_COLUMN(col), renderer, TRUE);
	gtk_tree_view_column_set_attributes(GTK_TREE_VIEW_COLUMN(col), renderer, "text", 1, NULL);
	// Adds the column to the tree view
	gtk_tree_view_append_column( GTK_TREE_VIEW(treeView), col );


	// Creates a new column for the tree view
	col = gtk_tree_view_column_new();
	// Sets the name of the column
	gtk_tree_view_column_set_title(col, "Éxitos");
	// Renders the column
	renderer = gtk_cell_renderer_text_new();
	gtk_tree_view_column_pack_start(GTK_TREE_VIEW_COLUMN(col), renderer, TRUE);
	gtk_tree_view_column_set_attributes(GTK_TREE_VIEW_COLUMN(col), renderer, "text", 2, NULL);
	// Adds the column to the tree view
	gtk_tree_view_append_column( GTK_TREE_VIEW(treeView), col );


	// Creates a new column for the tree view
	col = gtk_tree_view_column_new();
	// Sets the name of the column
	gtk_tree_view_column_set_title(col, "Fallos");
	// Renders the column
	renderer = gtk_cell_renderer_text_new();
	gtk_tree_view_column_pack_start(GTK_TREE_VIEW_COLUMN(col), renderer, TRUE);
	gtk_tree_view_column_set_attributes(GTK_TREE_VIEW_COLUMN(col), renderer, "text", 3, NULL);
	// Adds the column to the tree view
	gtk_tree_view_append_column( GTK_TREE_VIEW(treeView), col );


	// Shows all the widget in the dialog
	gtk_widget_show_all(dialog);
	// Blocks in a recursive loop until the dialog either emits the 'response' signal, or is destroyed
	gtk_dialog_run( GTK_DIALOG(dialog) );
	// Destroys the dialog
	gtk_widget_destroy(dialog);
}


/**
 Shows a dialog to enter the data of a new specialist.

 @param [in] widget Pointer to the widget which call this function.
 @param [in] data A gpointer that point to the data sended in the function where this function was called.

 @return Nothing.
*/
void addSpecialistDialog(GtkWidget *widget, gpointer data)
{
	GtkWidget *dialog;
	GtkWidget *idLabel, *nameLabel, *specialtyLabel;
	GtkWidget *idEntry, *nameEntry, *specialtyEntry;
	GtkWidget *grid;
	GtkWidget *vbox;
	GtkWidget *addButton;
	GtkWidget *keyboardButton;
	int keyboardOptions[2] = {2, 1};


	// Creates the dialog box
	dialog = gtk_dialog_new();
	// Sets the title for the dialog
	gtk_window_set_title( GTK_WINDOW(dialog), "Añadir un nuevo especialista" );

	// Creates the entry to input the identification number (id) of the specialist
	idEntry = gtk_entry_new();
	// Creates the entry to input the specialist name
	nameEntry = gtk_entry_new();
	// Creates the entry to input the specialty of the specialist
	specialtyEntry = gtk_entry_new();
	// Creates a label to explain the id entry
	idLabel = gtk_label_new("Número identificativo:");
	// Creates a label to explain the specialist name entry
	nameLabel = gtk_label_new("Nombre completo:");
	// Creates a label to explain the specialty entry
	specialtyLabel = gtk_label_new("Especialidad:");

	// Creates a container of widgets
	grid = gtk_grid_new();
	// Inserts the widgets in that container
	gtk_grid_attach( GTK_GRID(grid), idLabel, 0, 0, 1, 1 );
	gtk_grid_attach( GTK_GRID(grid), idEntry, 1, 0, 1, 1 );
	gtk_grid_attach( GTK_GRID(grid), nameLabel, 0, 1, 1, 1 );
	gtk_grid_attach( GTK_GRID(grid), nameEntry, 1, 1, 1, 1 );
	gtk_grid_attach( GTK_GRID(grid), specialtyLabel, 0, 2, 1, 1 );
	gtk_grid_attach( GTK_GRID(grid), specialtyEntry, 1, 2, 1, 1 );

	// Creates a vertical box container, contained inside of the dialog
	vbox = gtk_dialog_get_content_area( GTK_DIALOG(dialog) );
	// Inserts the grid into the vertical box
	gtk_box_pack_start( GTK_BOX(vbox), grid, FALSE, FALSE, 1 );


	// Data to be sent to the callback function
	g_object_set_data( G_OBJECT(dialog), "idEntry", idEntry );
	g_object_set_data( G_OBJECT(dialog), "nameEntry", nameEntry );
	g_object_set_data( G_OBJECT(dialog), "specialtyEntry", specialtyEntry );
	g_object_set_data( G_OBJECT(dialog), "dialog", dialog );


	// Creates the keyboard button
 	keyboardButton = gtk_button_new_with_label("Teclado virtual");
	// Calls a callback function when the keyboard button is clicked
	g_signal_connect(keyboardButton, "clicked", G_CALLBACK(runKeyboard), keyboardOptions);
	// Adds the keyboard button to the dialog
	gtk_dialog_add_action_widget( GTK_DIALOG(dialog), keyboardButton, GTK_RESPONSE_APPLY );

	// Creates the add button
 	addButton = gtk_button_new_with_label("Añadir");
	// Calls a callback function when the add button is clicked
	g_signal_connect(addButton, "clicked", G_CALLBACK(addSpecialist), dialog);
	// Adds the add button to the dialog
	gtk_dialog_add_action_widget( GTK_DIALOG(dialog), addButton, GTK_RESPONSE_APPLY );

	// Adds a cancel button
	gtk_dialog_add_button( GTK_DIALOG(dialog), "Cancelar", GTK_RESPONSE_CANCEL );


	// Shows all the widget in the dialog
	gtk_widget_show_all(dialog);
	// Blocks in a recursive loop until the dialog either emits the 'response' signal, or is destroyed
	gtk_dialog_run( GTK_DIALOG(dialog) );
	// Destroys the dialog
	gtk_widget_destroy(dialog);
}


/**
 Shows a dialog where the user can enter the new data of a specialist.

 @param [in] widget Pointer to the widget which call this function.
 @param [in] data A gpointer that point to the data sended in the function where this function was called.

 @return Nothing.
*/
void updateSpecialistDialog(GtkWidget *widget, gpointer data)
{
	GtkWidget *dialog;
	GtkWidget *idLabel, *nameLabel, *specialtyLabel;
	GtkWidget *idEntry, *nameEntry, *specialtyEntry;
	GtkWidget *updateButton;
	GtkWidget *vbox, *hbox1, *hbox2;
	GtkWidget *grid;
	Database db1;
	Specialist specialist1;
	int posSpecialist;


	// Gets the data sent
	GtkWidget *dialogCbox = (GtkWidget*)g_object_get_data( G_OBJECT(data), "dialogCbox" );


	// Creates the dialog box
	dialog = gtk_dialog_new();
	// Sets the title of the dialog
	gtk_window_set_title( GTK_WINDOW(dialog), "Modificar especialista" );

	// Gets the specialist selected in the combobox
	posSpecialist = gtk_combo_box_get_active( GTK_COMBO_BOX(dialogCbox) );

	// Gets the specialist data from the database
	db1.getNSpecialist(posSpecialist, specialist1);


	// Creates a entry to input the identification number (id) of the specialist
	idEntry = gtk_entry_new();
	// Sets the value by default
	gtk_entry_set_text( GTK_ENTRY(idEntry), specialist1.id.c_str() );

	// Creates a entry to input the specialist name
	nameEntry = gtk_entry_new();
	// Sets the value by default
	gtk_entry_set_text( GTK_ENTRY(nameEntry), specialist1.name.c_str() );

	// Creates a entry to input the specialty of the specialist
	specialtyEntry = gtk_entry_new();
	// Sets the value by default
	gtk_entry_set_text( GTK_ENTRY(specialtyEntry), specialist1.specialty.c_str() );


	// Creates a label to explain the id entry
	idLabel = gtk_label_new("Número identificativo:");
	// Creates a label to explain the name entry
	nameLabel = gtk_label_new("Nombre completo:");
	// Creates a label to explain the specialty entry
	specialtyLabel = gtk_label_new("Especialidad:");


	// Creates a container of widgets
	grid = gtk_grid_new();
	// Inserts the widgets in that container
	gtk_grid_attach( GTK_GRID(grid), idLabel, 0, 0, 1, 1 );
	gtk_grid_attach( GTK_GRID(grid), idEntry, 1, 0, 1, 1 );
	gtk_grid_attach( GTK_GRID(grid), nameLabel, 0, 1, 1, 1 );
	gtk_grid_attach( GTK_GRID(grid), nameEntry, 1, 1, 1, 1 );
	gtk_grid_attach( GTK_GRID(grid), specialtyLabel, 0, 2, 1, 1 );
	gtk_grid_attach( GTK_GRID(grid), specialtyEntry, 1, 2, 1, 1 );

	// Creates a vertical box container, contained inside of the dialog
	vbox = gtk_dialog_get_content_area( GTK_DIALOG(dialog) );
	// Inserts the grid into the vertical box
	gtk_box_pack_start( GTK_BOX(vbox), grid, FALSE, FALSE, 1 );


	// Data to be sent to the callback function
	g_object_set_data( G_OBJECT(dialog), "idEntry", idEntry );
	g_object_set_data( G_OBJECT(dialog), "nameEntry", nameEntry );
	g_object_set_data( G_OBJECT(dialog), "specialtyEntry", specialtyEntry );
	g_object_set_data( G_OBJECT(dialog), "dialogCbox", dialogCbox );


	// Creates the update button
 	updateButton = gtk_button_new_with_label("Modificar");
	// Calls a callback function when the add button is clicked
	g_signal_connect(updateButton, "clicked", G_CALLBACK(updateSpecialist), dialog);
	// Adds the action button to the dialog
	gtk_dialog_add_action_widget( GTK_DIALOG(dialog), updateButton, GTK_RESPONSE_APPLY );

	// Adds a cancel button
	gtk_dialog_add_button( GTK_DIALOG(dialog), "Cancelar", GTK_RESPONSE_CANCEL );


	// Shows all the widget in the dialog
	gtk_widget_show_all(dialog);
	// Blocks in a recursive loop until the dialog either emits the 'response' signal, or is destroyed
	gtk_dialog_run( GTK_DIALOG(dialog) );
	// Destroys the dialog
	gtk_widget_destroy(dialog);
}


/**
 Shows a dialog to choose a specialist to be updated or deleted.

 @param [in] widget Pointer to the widget which call this function.
 @param [in] data A gpointer that point to the data sended in the function where this function was called.

 @return Nothing.
*/
void chooseSpecialistDialog(GtkWidget *widget, gpointer data)
{
	GtkWidget *dialog;
	GtkWidget *label;
	GtkWidget *dialogCbox;
	GtkWidget *grid;
	GtkWidget *vbox;
	GtkWidget *button;
	GtkListStore *dialogListstore;

	Database db1;
	const gchar *nameData;
	const gchar *idData;


	// Creates the dialog box
	dialog = gtk_dialog_new();
	// Sets the title of the dialog
	if( strcmp( gtk_button_get_label( GTK_BUTTON(widget) ), "Eliminar especialista") == 0 )
		gtk_window_set_title( GTK_WINDOW(dialog), "Eliminar especialista" );
	else if( strcmp( gtk_button_get_label( GTK_BUTTON(widget) ), "Modificar especialista") == 0 )
		gtk_window_set_title( GTK_WINDOW(dialog), "Modificar especialista" );


	// Creates the specialists combobox
	createSpecialistsCbox(&dialogCbox, &dialogListstore);

	// Creates a label to explain the specialists combobox
	label = gtk_label_new("Elige el especialista:");


	// Creates a container of widgets
	grid = gtk_grid_new();
	// Inserts the widgets in that container
	gtk_grid_attach( GTK_GRID(grid), label, 0, 0, 1, 1 );
	gtk_grid_attach( GTK_GRID(grid), dialogCbox, 1, 0, 1, 1 );

	// Creates a vertical box container, contained inside of the dialog
	vbox = gtk_dialog_get_content_area( GTK_DIALOG(dialog) );
	// Inserts the grid into the vertical box
	gtk_box_pack_start( GTK_BOX(vbox), grid, FALSE, FALSE, 1 );

	
	// Data to be sent to the callback function
	g_object_set_data( G_OBJECT(dialog), "dialogCbox", dialogCbox );


	if( strcmp( gtk_button_get_label( GTK_BUTTON(widget) ), "Eliminar especialista") == 0 )
	{
		// Creates the delete button
	 	button = gtk_button_new_with_label("Eliminar");
		// Calls a callback function when the delete button is clicked
		g_signal_connect(button, "clicked", G_CALLBACK(deleteSpecialist), dialog);
	}
	else if( strcmp( gtk_button_get_label( GTK_BUTTON(widget) ), "Modificar especialista") == 0 )
	{
		// Creates the update button
	 	button = gtk_button_new_with_label("Modificar");
		// Calls a callback function when the update button is clicked
		g_signal_connect(button, "clicked", G_CALLBACK(updateSpecialistDialog), dialog);
	}
	// Adds the action button to the dialog
	gtk_dialog_add_action_widget( GTK_DIALOG(dialog), button, GTK_RESPONSE_APPLY );
	// Adds a cancel button
	gtk_dialog_add_button( GTK_DIALOG(dialog), "Cancelar", GTK_RESPONSE_CANCEL );


	// Shows all the widget in the dialog
	gtk_widget_show_all(dialog);
	// Blocks in a recursive loop until the dialog either emits the 'response' signal, or is destroyed
	gtk_dialog_run( GTK_DIALOG(dialog) );
	// Destroys the dialog
	gtk_widget_destroy(dialog);
}


/**
 Shows a dialog to show the list of specialists.

 @param [in] widget Pointer to the widget which call this function.
 @param [in] data A gpointer that point to the data sended in the function where this function was called.

 @return Nothing.
*/
void specialistsListDialog(GtkWidget *widget, gpointer data)
{
	GtkWidget *dialog;
	GtkWidget *vbox;
	GtkWidget *treeView;
	GtkListStore *liststore;
	GtkTreeIter iter;
	GtkTreeViewColumn *col;
	GtkCellRenderer *renderer;
	Database db1;
	Specialist specialist1;
	int tableSize = 0;
	
	// Creates a new dialog
	dialog = gtk_dialog_new();
	// Sets the size of the dialog
	gtk_window_set_default_size( GTK_WINDOW(dialog), 400, 300 );
	// Sets the name of the dialog
	gtk_window_set_title( GTK_WINDOW(dialog), "Lista de especialistas" );
	// Gets the content area of the dialog
	vbox = gtk_dialog_get_content_area( GTK_DIALOG(dialog) );

	// Creates a list store, to store the list of specialists
	liststore = gtk_list_store_new(3, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
	// Gets the size of the table of specialists
	db1.getSpecialistsTableSize(tableSize);
	// Saves all the specialists in the list store
	for(int row = 0; row < tableSize; row++)
	{
		db1.getNSpecialist(row, specialist1);

		gtk_list_store_append(liststore, &iter);
		gtk_list_store_set(liststore, &iter, 0, specialist1.id.c_str(), 1, specialist1.name.c_str(), 2, specialist1.specialty.c_str(), -1);
	}

	// Creates a tree view with the previous list store
	treeView = gtk_tree_view_new_with_model( GTK_TREE_MODEL(liststore) );
	// Inserts the tree view in the dialog
	gtk_box_pack_start( GTK_BOX(vbox), treeView, FALSE, FALSE, 1 );


	// Creates a new column for the tree view
	col = gtk_tree_view_column_new();
	// Sets the name of the column
	gtk_tree_view_column_set_title(col, "ID");
	// Renders the column
	renderer = gtk_cell_renderer_text_new();
	gtk_tree_view_column_pack_start(GTK_TREE_VIEW_COLUMN(col), renderer, FALSE);
	gtk_tree_view_column_set_attributes(GTK_TREE_VIEW_COLUMN(col), renderer, "text", 0, NULL);
	// Adds the column to the tree view
	gtk_tree_view_append_column( GTK_TREE_VIEW(treeView), col );


	// Creates a new column for the tree view
	col = gtk_tree_view_column_new();
	// Sets the name of the column
	gtk_tree_view_column_set_title(col, "Nombre");
	// Renders the column
	renderer = gtk_cell_renderer_text_new();
	gtk_tree_view_column_pack_start(GTK_TREE_VIEW_COLUMN(col), renderer, FALSE);
	gtk_tree_view_column_set_attributes(GTK_TREE_VIEW_COLUMN(col), renderer, "text", 1, NULL);
	// Adds the column to the tree view
	gtk_tree_view_append_column( GTK_TREE_VIEW(treeView), col );


	// Creates a new column for the tree view
	col = gtk_tree_view_column_new();
	// Sets the name of the column
	gtk_tree_view_column_set_title(col, "Especialidad");
	// Renders the column
	renderer = gtk_cell_renderer_text_new();
	gtk_tree_view_column_pack_start(GTK_TREE_VIEW_COLUMN(col), renderer, FALSE);
	gtk_tree_view_column_set_attributes(GTK_TREE_VIEW_COLUMN(col), renderer, "text", 2, NULL);
	// Adds the column to the tree view
	gtk_tree_view_append_column( GTK_TREE_VIEW(treeView), col );


	// Shows all the widget in the dialog
	gtk_widget_show_all(dialog);
	// Blocks in a recursive loop until the dialog either emits the 'response' signal, or is destroyed
	gtk_dialog_run( GTK_DIALOG(dialog) );
	// Destroys the dialog
	gtk_widget_destroy(dialog);
}


/**
 Shows a dialog to choose the user and the specialist to be linked.

 @param [in] widget Pointer to the widget which call this function.
 @param [in] data A gpointer that point to the data sended in the function where this function was called.

 @return Nothing.
*/
void userSpecialistDialog(GtkWidget *widget, gpointer data)
{
	GtkWidget *dialog;
	GtkWidget *usersDialogCbox, *specialistDialogCbox;
	GtkWidget *usersLabel, *specialistsLabel;
	GtkWidget *grid;
	GtkWidget *vbox;
	GtkWidget *button;
	GtkListStore *usersListstore, *specialistsListstore;


	// Creates the dialog box
	dialog = gtk_dialog_new();
	// Sets the title of the dialog
	if( strcmp( gtk_button_get_label( GTK_BUTTON(widget) ), "Vincular usuario y especialista") == 0 )
		gtk_window_set_title( GTK_WINDOW(dialog), "Vincular usuario y especialista" );
	else if( strcmp( gtk_button_get_label( GTK_BUTTON(widget) ), "Desvincular usuario y especialista") == 0 )
		gtk_window_set_title( GTK_WINDOW(dialog), "Desvincular usuario y especialista" );

	// Creates a users combobox
	createUsersCbox(&usersDialogCbox, &usersListstore);

	// Creates a specialists combobox
	createSpecialistsCbox(&specialistDialogCbox, &specialistsListstore);

	// Creates a label to explain the users combobox
	usersLabel = gtk_label_new("Elige el usuario:");

	// Creates a label to explain the specialists combobox
	specialistsLabel = gtk_label_new("Elige el especialista:");


	// Creates a container of widgets
	grid = gtk_grid_new();
	// Inserts the widgets in that container
	gtk_grid_attach( GTK_GRID(grid), usersLabel, 0, 0, 1, 1 );
	gtk_grid_attach( GTK_GRID(grid), usersDialogCbox, 1, 0, 1, 1 );
	gtk_grid_attach( GTK_GRID(grid), specialistsLabel, 0, 1, 1, 1 );
	gtk_grid_attach( GTK_GRID(grid), specialistDialogCbox, 1, 1, 1, 1 );

	// Creates a vertical box container, contained inside of the dialog
	vbox = gtk_dialog_get_content_area( GTK_DIALOG(dialog) );
	// Inserts the grid into the vertical box
	gtk_box_pack_start( GTK_BOX(vbox), grid, FALSE, FALSE, 1 );


	// Data to be sent to the callback function
	g_object_set_data( G_OBJECT(dialog), "usersDialogCbox", usersDialogCbox );
	g_object_set_data( G_OBJECT(dialog), "specialistDialogCbox", specialistDialogCbox );


	if( strcmp( gtk_button_get_label( GTK_BUTTON(widget) ), "Vincular usuario y especialista") == 0 )
	{
		// Creates the link button
		button = gtk_button_new_with_label("Vincular");
		// Calls a callback function when the link button is clicked
		g_signal_connect(button, "clicked", G_CALLBACK(linkUserSpecialist), dialog);
	}
	else if( strcmp( gtk_button_get_label( GTK_BUTTON(widget) ), "Desvincular usuario y especialista") == 0 )
	{
		// Creates the link button
		button = gtk_button_new_with_label("Desvincular");
		// Calls a callback function when the link button is clicked
		g_signal_connect(button, "clicked", G_CALLBACK(unlinkUserSpecialist), dialog);
	}


	// Adds the action button to the dialog
	gtk_dialog_add_action_widget( GTK_DIALOG(dialog), button, GTK_RESPONSE_APPLY );
	// Adds a cancel button
	gtk_dialog_add_button( GTK_DIALOG(dialog), "Cancelar", GTK_RESPONSE_CANCEL );


	// Shows all the widget in the dialog
	gtk_widget_show_all(dialog);
	// Blocks in a recursive loop until the dialog either emits the 'response' signal, or is destroyed
	gtk_dialog_run( GTK_DIALOG(dialog) );
	// Destroys the dialog
	gtk_widget_destroy(dialog);
}



int main(int argc, char *argv[])
{
	GtkWidget *mainWindow;
	GtkWidget *notebook;
	GtkWidget *vbox;
	GtkWidget *playTabVbox, *playTabHbox1, *playTabHbox2;
	GtkWidget *dbManagementVbox, *dbManagementHbox1, *dbManagementHbox2;
	GtkWidget *settingsFrame, *userFrame;
	GtkWidget *settingsGrid, *userGrid, *playGrid;
	GtkWidget *usersCbox;
	GtkWidget *gameDurationEntry, *fruitDurationEntry;
	GtkWidget *usersLabel, *gameDurationLabel, *fruitDurationLabel;
	GtkWidget *playButton;
	GtkWidget *addUserButton, *deleteUserButton, *updateUserButton, *userListButton;
	GtkWidget *addSpecialistButton, *deleteSpecialistButton, *updateSpecialistButton, *specialistListButton;
	GtkWidget *userSpecialistLinkButton, *userSpecialistUnlinkButton;
	GtkWidget *userButtonsGrid, *specialistButtonsGrid, *linkButtonsGrid;
	GtkWidget *userManagementFrame, *specialistManagementFrame, *linkManagementFrame;
	GtkWidget *exportButtonsGrid;
	GtkWidget *exportGameDataButton, *exportUserGamesButton, *exportUsersListButton, *exportSpecialistsListButton;
	GtkWidget *menu, *about, *menubar;

	const gchar *gameDurationBuffer;
	const gchar *fruitDurationBuffer;
	Database db1;
	User user1;
	int tableSize = 0;
	const gchar *nameData;
	const gchar *idData;
	GtkListStore *liststore;
	GtkTreeIter iter;
	GtkCellRenderer *cellrenderertext;


	// Initializes everything needed to operate the toolkit and parses arguments from the command line to the application
	gtk_init(&argc, &argv);

	// Creates the main window
	mainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	// Sets the title for the main window
	gtk_window_set_title( GTK_WINDOW(mainWindow), "Sistema Kinect para el desarrollo de la motricidad gruesa" ); 

	// Closes the application if the x button located in the upper right corner is pressed
	g_signal_connect(mainWindow, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	// Shows the main window in the screen center
	gtk_window_set_position( GTK_WINDOW(mainWindow), GTK_WIN_POS_CENTER );


	//////////////////
	//// PLAY TAB ////
	//////////////////
	// Creates a list store, to store the list of users
	liststore = gtk_list_store_new(2, G_TYPE_STRING, G_TYPE_STRING);

	// Creates the users combobox
	createUsersCbox(&usersCbox, &liststore);

	// Creates a label to explain the users combobox
	usersLabel = gtk_label_new("Elige un usuario:");

	// Creates the container of widgets for the select user frame
	userGrid = gtk_grid_new();
	// Sets the border of the user grid
	gtk_container_set_border_width(GTK_CONTAINER(userGrid), 9);
	// Inserts the widgets in that container
	gtk_grid_attach( GTK_GRID(userGrid), usersLabel, 0, 0, 1, 1 );
	gtk_grid_attach( GTK_GRID(userGrid), usersCbox, 1, 0, 1, 1 );

	// Creates the user frame
	userFrame = gtk_frame_new("Jugador");
	// Sets the border of the user frame
	gtk_container_set_border_width(GTK_CONTAINER(userFrame), 8);
	// Inserts the user grid into the user frame
	gtk_container_add( GTK_CONTAINER(userFrame), userGrid );


	// Creates the entry to input the duration of the game
	gameDurationEntry = gtk_entry_new();
	// By default, shows a value of 60 seconds
	gameDurationBuffer = "60";
	gtk_entry_set_text( GTK_ENTRY(gameDurationEntry), gameDurationBuffer );
	
	// Creates the entry to input the duration of the fruit
	fruitDurationEntry = gtk_entry_new();
	// By default, shows a value of 3 seconds
	fruitDurationBuffer = "3";
	gtk_entry_set_text( GTK_ENTRY(fruitDurationEntry), fruitDurationBuffer );

	// Creates a label to explain the entry for the duration of the game
	gameDurationLabel = gtk_label_new("Duración de juego (segundos):");
	
	// Creates a label to explain the entry for the duration of the fruit
	fruitDurationLabel = gtk_label_new("Duración de fruta (segundos):");

	// Creates the container of widgets for the settings frame
	settingsGrid = gtk_grid_new();
	// Sets the border of the settings grid
	gtk_container_set_border_width(GTK_CONTAINER(settingsGrid), 9);
	// Inserts the widgets into that container
	gtk_grid_attach( GTK_GRID(settingsGrid), gameDurationLabel, 0, 0, 1, 1 );
	gtk_grid_attach( GTK_GRID(settingsGrid), fruitDurationLabel, 0, 1, 1, 1 );
	gtk_grid_attach( GTK_GRID(settingsGrid), gameDurationEntry, 1, 0, 1, 1 );
	gtk_grid_attach( GTK_GRID(settingsGrid), fruitDurationEntry, 1, 1, 1, 1 );

	// Creates the settings frame
	settingsFrame = gtk_frame_new("Configuración");
	// Sets the border of settings frame
	gtk_container_set_border_width(GTK_CONTAINER(settingsFrame), 8);
	// Inserts the setting grid into the setting frame
	gtk_container_add( GTK_CONTAINER(settingsFrame), settingsGrid );


	// Creates the play button
	playButton = gtk_button_new_with_label("Jugar");
	g_signal_connect(playButton, "clicked", G_CALLBACK(runGame), mainWindow);
	// Sets the button size
	gtk_widget_set_size_request(playButton, -1, 60);

	// Creates the container of widgets for the play tab
	playGrid = gtk_grid_new();
	// Inserts the widgets into that container
	gtk_grid_attach( GTK_GRID(playGrid), userFrame, 0, 0, 1, 1 );
	gtk_grid_attach( GTK_GRID(playGrid), settingsFrame, 1, 0, 1, 1 );
	gtk_grid_attach( GTK_GRID(playGrid), playButton, 0, 1, 2, 1 );


	// Creates the 'play tab vertical box'
	playTabVbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
	// Adds the play grid inside the vertical box
	gtk_box_pack_start((GtkBox*)playTabVbox, playGrid, FALSE, FALSE, 1);


	// Data to be sent to the callback functions
	g_object_set_data( G_OBJECT(mainWindow), "fruitDurationEntry", fruitDurationEntry );
	g_object_set_data( G_OBJECT(mainWindow), "gameDurationEntry", gameDurationEntry );
	g_object_set_data( G_OBJECT(mainWindow), "usersCbox", usersCbox );
	g_object_set_data( G_OBJECT(mainWindow), "liststore", liststore );


	/////////////////////////////////
	//// DATABASE MANAGEMENT TAB ////
	/////////////////////////////////
	// Creates a 'add user' button
	addUserButton = gtk_button_new_with_label("Añadir usuario");
	// Sets the button size
	gtk_widget_set_size_request(addUserButton, 160, 60);
	// Calls a callback function when the button is clicked
	g_signal_connect(addUserButton, "clicked", G_CALLBACK(addUserDialog), mainWindow);

	// Creates a 'delete user' button
	deleteUserButton = gtk_button_new_with_label("Eliminar usuario");
	// Sets the button size
	gtk_widget_set_size_request(deleteUserButton, 160, 60);
	// Calls a callback function when the button is clicked
	g_signal_connect(deleteUserButton, "clicked", G_CALLBACK(chooseUserDialog), mainWindow);

	// Creates a 'update user' button
	updateUserButton = gtk_button_new_with_label("Modificar usuario");
	// Sets the button size
	gtk_widget_set_size_request(updateUserButton, 160, 60);
	// Calls a callback function when the button is clicked
	g_signal_connect(updateUserButton, "clicked", G_CALLBACK(chooseUserDialog), mainWindow);

	// Creates a 'show users list' button
	userListButton = gtk_button_new_with_label("Lista de usuarios");
	// Sets the button size
	gtk_widget_set_size_request(userListButton, 160, 60);
	// Calls a callback function when the button is clicked
	g_signal_connect(userListButton, "clicked", G_CALLBACK(usersListDialog), NULL);

	// Creates the container of buttons for the user management
	userButtonsGrid = gtk_grid_new();
	// Sets the border of the user buttons grid
	gtk_container_set_border_width(GTK_CONTAINER(userButtonsGrid), 3);
	// Inserts the buttons into that container
	gtk_grid_attach( GTK_GRID(userButtonsGrid), addUserButton, 0, 0, 1, 1 );
	gtk_grid_attach( GTK_GRID(userButtonsGrid), deleteUserButton, 1, 0, 1, 1 );
	gtk_grid_attach( GTK_GRID(userButtonsGrid), updateUserButton, 0, 1, 1, 1 );
	gtk_grid_attach( GTK_GRID(userButtonsGrid), userListButton, 1, 1, 1, 1 );

	// Creates the user manegement frame
	userManagementFrame = gtk_frame_new("Gestión de usuarios");
	// Sets the border of that frame
	gtk_container_set_border_width(GTK_CONTAINER(userManagementFrame), 3);
	// Inserts the setting grid into the setting frame
	gtk_container_add( GTK_CONTAINER(userManagementFrame), userButtonsGrid );
	

	// Creates a 'add specialist' button
	addSpecialistButton = gtk_button_new_with_label("Añadir especialista");
	// Sets the button size
	gtk_widget_set_size_request(addSpecialistButton, 160, 60);
	// Calls a callback function when the button is clicked
	g_signal_connect(addSpecialistButton, "clicked", G_CALLBACK(addSpecialistDialog), NULL);

	// Creates a 'delete specialist' button
	deleteUserButton = gtk_button_new_with_label("Eliminar especialista");
	// Sets the button size
	gtk_widget_set_size_request(deleteUserButton, 160, 60);
	// Calls a callback function when the button is clicked
	g_signal_connect(deleteUserButton, "clicked", G_CALLBACK(chooseSpecialistDialog), NULL);

	// Creates a 'update specialist' button
	updateSpecialistButton = gtk_button_new_with_label("Modificar especialista");
	// Sets the button size
	gtk_widget_set_size_request(updateSpecialistButton, 160, 60);
	// Calls a callback function when the button is clicked
	g_signal_connect(updateSpecialistButton, "clicked", G_CALLBACK(chooseSpecialistDialog), NULL);

	// Creates a 'show specialist list' button
	specialistListButton = gtk_button_new_with_label("Lista de especialistas");
	// Sets the button size
	gtk_widget_set_size_request(specialistListButton, 160, 60);
	// Calls a callback function when the button is clicked
	g_signal_connect(specialistListButton, "clicked", G_CALLBACK(specialistsListDialog), NULL);

	// Creates the container of buttons for the user management
	specialistButtonsGrid = gtk_grid_new();
	// Sets the border of the specialist buttons grid
	gtk_container_set_border_width(GTK_CONTAINER(specialistButtonsGrid), 3);
	// Inserts the buttons into that container
	gtk_grid_attach( GTK_GRID(specialistButtonsGrid), addSpecialistButton, 0, 0, 1, 1 );
	gtk_grid_attach( GTK_GRID(specialistButtonsGrid), deleteUserButton, 1, 0, 1, 1 );
	gtk_grid_attach( GTK_GRID(specialistButtonsGrid), updateSpecialistButton, 0, 1, 1, 1 );
	gtk_grid_attach( GTK_GRID(specialistButtonsGrid), specialistListButton, 1, 1, 1, 1 );

	// Creates the specialists manegement frame
	specialistManagementFrame = gtk_frame_new("Gestión de especialistas");
	// Sets the border of that frame
	gtk_container_set_border_width(GTK_CONTAINER(specialistManagementFrame), 3);
	// Inserts the setting grid into the setting frame
	gtk_container_add( GTK_CONTAINER(specialistManagementFrame), specialistButtonsGrid );


	// Creates a 'link user and specialist' button
	userSpecialistLinkButton = gtk_button_new_with_label("Vincular usuario y especialista");
	// Sets the button size
	gtk_widget_set_size_request(userSpecialistLinkButton, 328, 60);
	// Calls a callback function when the button is clicked
	g_signal_connect(userSpecialistLinkButton, "clicked", G_CALLBACK(userSpecialistDialog), NULL);

	// Creates a 'unlink user and specialist' button
	userSpecialistUnlinkButton = gtk_button_new_with_label("Desvincular usuario y especialista");
	// Sets the button size
	gtk_widget_set_size_request(userSpecialistUnlinkButton, 328, 60);
	// Calls a callback function when the button is clicked
	g_signal_connect(userSpecialistUnlinkButton, "clicked", G_CALLBACK(userSpecialistDialog), NULL);

	// Creates the container of buttons for the link management
	linkButtonsGrid = gtk_grid_new();
	// Sets the border of the link buttons grid
	gtk_container_set_border_width(GTK_CONTAINER(linkButtonsGrid), 3);
	// Inserts the buttons into that container
	gtk_grid_attach( GTK_GRID(linkButtonsGrid), userSpecialistLinkButton, 0, 0, 1, 1 );
	gtk_grid_attach( GTK_GRID(linkButtonsGrid), userSpecialistUnlinkButton, 1, 0, 1, 1 );

	// Creates the link management frame
	linkManagementFrame = gtk_frame_new("Vinculación usuario-especialista");
	// Sets the border of that frame
	gtk_container_set_border_width(GTK_CONTAINER(linkManagementFrame), 3);
	// Inserts the setting grid into the setting frame
	gtk_container_add( GTK_CONTAINER(linkManagementFrame), linkButtonsGrid );


	// Creates the first 'management horizontal box'
	dbManagementHbox1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
	// Inserts the widgets into that 'management horizontal box'
	gtk_box_pack_start( GTK_BOX(dbManagementHbox1), userManagementFrame, FALSE, FALSE, 1 );
	gtk_box_pack_start( GTK_BOX(dbManagementHbox1), specialistManagementFrame, FALSE, FALSE, 1 );

	// Creates the second 'management horizontal box'
	dbManagementHbox2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
	// Inserts the widgets into that 'management horizontal box'
	gtk_box_pack_start( GTK_BOX(dbManagementHbox2), linkManagementFrame, FALSE, FALSE, 1 );

	// Creates the 'management vertical box' to contain all the horizontal boxes
	dbManagementVbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
	// Inserts the widgets into that 'management horizontal box'
	gtk_box_pack_start( GTK_BOX(dbManagementVbox), dbManagementHbox1, FALSE, FALSE, 1 );
	gtk_box_pack_start( GTK_BOX(dbManagementVbox), dbManagementHbox2, FALSE, FALSE, 1 );


	/////////////////////////////////
	//// GRID OF DATA EXPORT TAB ////
	/////////////////////////////////

	// Creates a button to export the games of a user
	exportUserGamesButton = gtk_button_new_with_label("Partidas de un usuario");
	// Sets the button size
	gtk_widget_set_size_request(exportUserGamesButton, 328, 60);
	// Calls a callback function when the button is clicked
	g_signal_connect(exportUserGamesButton, "clicked", G_CALLBACK(chooseUserDialog), mainWindow);

	// Creates a button to export the data of a game
	exportGameDataButton = gtk_button_new_with_label("Datos de una partida");
	// Sets the button size
	gtk_widget_set_size_request(exportGameDataButton, 328, 80);
	// Calls a callback function when the button is clicked
	g_signal_connect(exportGameDataButton, "clicked", G_CALLBACK(chooseUserDialog), mainWindow);

	// Creates a button to export the list of users
	exportUsersListButton = gtk_button_new_with_label("Lista de usuarios");
	// Sets the button size
	gtk_widget_set_size_request(exportUsersListButton, 328, 80);
	// Calls a callback function when the button is clicked
	g_signal_connect(exportUsersListButton, "clicked", G_CALLBACK(exportUsersList), NULL);


	// Creates a button to export the list of users
	exportSpecialistsListButton = gtk_button_new_with_label("Lista de especialistas");
	// Sets the button size
	gtk_widget_set_size_request(exportSpecialistsListButton, 328, 80);
	// Calls a callback function when the button is clicked
	g_signal_connect(exportSpecialistsListButton, "clicked", G_CALLBACK(exportSpecialistsList), NULL);


	// Creates the container of buttons for the data export tab
	exportButtonsGrid = gtk_grid_new();
	// Sets the border of that grid
	gtk_container_set_border_width(GTK_CONTAINER(exportButtonsGrid), 9);
	// Inserts the buttons into that container
	gtk_grid_attach( GTK_GRID(exportButtonsGrid), exportUserGamesButton, 0, 0, 1, 1 );
	gtk_grid_attach( GTK_GRID(exportButtonsGrid), exportGameDataButton, 1, 0, 1, 1 );
	gtk_grid_attach( GTK_GRID(exportButtonsGrid), exportUsersListButton, 0, 1, 1, 1 );
	gtk_grid_attach( GTK_GRID(exportButtonsGrid), exportSpecialistsListButton, 1, 1, 1, 1 );


	///////////////////////////
	//// NOTEBOOK FOR TABS ////
	///////////////////////////
	// Creates the notebook
	notebook = gtk_notebook_new();

	// Adds the notebook to the window
	gtk_container_add( GTK_CONTAINER(mainWindow), notebook );

	// Sets the notebook in the top position of the main window
	gtk_notebook_set_tab_pos( GTK_NOTEBOOK(notebook), GTK_POS_TOP );

	// Adds the tabs in the notebook
	gtk_notebook_insert_page( GTK_NOTEBOOK(notebook), playTabVbox, gtk_label_new("Juego"), 0 );
    gtk_notebook_insert_page( GTK_NOTEBOOK(notebook), dbManagementVbox, gtk_label_new("Gestión de base de datos"), 1 );
	gtk_notebook_insert_page( GTK_NOTEBOOK(notebook), exportButtonsGrid, gtk_label_new("Exportar datos"), 2 );


	// Shows all the widgets by calling gtk_widget_show_all() on the window.
	gtk_widget_show_all(mainWindow);
	// Waits for an event to occur (like a key press or a mouse event), until gtk_main_quit() is called.
	gtk_main();
}

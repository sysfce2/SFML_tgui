/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2023 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef TGUI_FILE_DIALOG_HPP
#define TGUI_FILE_DIALOG_HPP


#include <TGUI/CopiedSharedPtr.hpp>
#include <TGUI/Widgets/Label.hpp>
#include <TGUI/Widgets/Button.hpp>
#include <TGUI/Widgets/EditBox.hpp>
#include <TGUI/Widgets/ComboBox.hpp>
#include <TGUI/Widgets/ListView.hpp>
#include <TGUI/Widgets/ChildWindow.hpp>
#include <TGUI/Widgets/Panel.hpp>
#include <TGUI/Renderers/FileDialogRenderer.hpp>
#include <TGUI/Filesystem.hpp>

#if !TGUI_EXPERIMENTAL_USE_STD_MODULE
    #include <tuple>
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TGUI_MODULE_EXPORT namespace tgui
{
    class FileDialogIconLoader;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief File dialog widget
    ///
    /// Open dialog:
    /// @code
    /// auto openFileDialog = tgui::FileDialog::create("Open file", "Open");
    /// @endcode
    ///
    /// Save dialog:
    /// @code
    /// auto saveFileDialog = tgui::FileDialog::create("Save file", "Save");
    /// saveFileDialog->setFileMustExist(false);
    /// @endcode
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API FileDialog : public ChildWindow
    {
    public:

        using Ptr = std::shared_ptr<FileDialog>; //!< Shared widget pointer
        using ConstPtr = std::shared_ptr<const FileDialog>; //!< Shared constant widget pointer

        static constexpr const char StaticWidgetType[] = "FileDialog"; //!< Type name of the widget


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /// @brief Constructor
        /// @param typeName     Type of the widget
        /// @param initRenderer Should the renderer be initialized? Should be true unless a derived class initializes it.
        /// @see create
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        FileDialog(const char* typeName = StaticWidgetType, bool initRenderer = true);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Creates a new file dialog widget
        ///
        /// @param title              Title to display in the title bar of the file dialog
        /// @param confirmButtonText  Caption of the open/save button
        /// @param allowCreateFolder  Determines if the user is allowed to create a folder
        ///
        /// @return The new file dialog
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD static FileDialog::Ptr create(const String& title = "Open file", const String& confirmButtonText = "Open", bool allowCreateFolder = false);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Copy constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        FileDialog(const FileDialog& copy);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Move constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        FileDialog(FileDialog&& copy) noexcept;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Overload of copy assignment operator
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        FileDialog& operator= (const FileDialog& right);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Overload of move assignment operator
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        FileDialog& operator= (FileDialog&& right) noexcept;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Makes a copy of another file dialog
        ///
        /// @param dialog  The other file dialog
        ///
        /// @return The new file dialog
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD static FileDialog::Ptr copy(const FileDialog::ConstPtr& dialog);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the renderer, which gives access to functions that determine how the widget is displayed
        /// @return Temporary pointer to the renderer that may be shared with other widgets using the same renderer
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD FileDialogRenderer* getSharedRenderer() override;
        TGUI_NODISCARD const FileDialogRenderer* getSharedRenderer() const override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the renderer, which gives access to functions that determine how the widget is displayed
        /// @return Temporary pointer to the renderer
        /// @warning After calling this function, the widget has its own copy of the renderer and it will no longer be shared.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD FileDialogRenderer* getRenderer() override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the selected files/directories
        ///
        /// @return File or directory that was selected in the file dialog
        ///
        /// Note that this function only returns a value once the open/save button is pressed (or a file is double-clicked).
        /// The value is set right before the onFileSelect signal is triggered.
        ///
        /// This function returns a path object from which the filename or full path name can be extracted.
        /// @code
        /// dialog->getSelectedPaths()[0].asString()     // Returns the entire path as a string (e.g. "/home/user/myfile.txt")
        /// dialog->getSelectedPaths()[0].getFilename()  // Returns only the filename component as a string (e.g. "myfile.txt")
        /// dialog->getSelectedPaths()[0].getParentPath().asString()  // Returns only the directory as a string (e.g. "/home/user/")
        /// @endcode
        ///
        /// If the file dialog is closed or the cancel button is pressed then the selected paths will be an empty list.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD const std::vector<Filesystem::Path>& getSelectedPaths() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the directory for which the files are to be displayed
        ///
        /// @param path  Directory to show in the file dialog
        ///
        /// There is another setPath function that takes a Filesystem::Path object instead of a String as parameter.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setPath(const String& path);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the directory for which the files are to be displayed
        ///
        /// @param path  Directory to show in the file dialog
        ///
        /// There is another setPath function that takes a String instead of a Filesystem::Path object as parameter.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setPath(const Filesystem::Path& path);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the directory that is currently being shown in the file dialog
        ///
        /// @return Path to displayed directory
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD const Filesystem::Path& getPath() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets the filename that is shown at the bottom of the file dialog
        ///
        /// @param filename  Filename to prefill
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setFilename(const String& filename);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the filename that is entered in the filename edit box
        ///
        /// @return Text entered in the filename edit box
        ///
        /// Note that this getter is associated with the setFilename setter which is intended for prefilling the filename when
        /// the dialog is open. Although this function does provide the filename of the currently selected file, the intended
        /// function to get the selected file when the dialog closes is getSelectedFile().
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD const String& getFilename() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the file filters which the user can select to only show files of a certain type
        ///
        /// @param filters             List of file type filters
        /// @param defaultFilterIndex  Index in the filter list to select by default
        ///
        /// Each filter contains of a pair. The first element of the pair is the string that is shown to the user in the
        /// combo box. The second element of the pair is a list of expressions that are matched with the filename.
        /// If the list of expressions is empty then all files will be shown. If it contains more than 1 string then a file is
        /// shown when it matches any of the expressions.
        ///
        /// Example usage:
        /// @code
        /// fileDialog->setFileTypeFilters({
        ///     {"Single extension", {"*.txt"}},
        ///     {"Multiple extension", {"*.png", "*.jpg"}},
        ///     {"Specific file", {"config.txt"}},
        ///     {"All files", {}}
        /// });
        /// @endcode
        ///
        /// @warning The wildcard is currently only supported as first character of the string
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setFileTypeFilters(const std::vector<std::pair<String, std::vector<String>>>& filters, std::size_t defaultFilterIndex = 0);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the file filters which the user can select to only show files of a certain type
        ///
        /// @return List of file type filters
        ///
        /// @see setFileTypeFilters
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD const std::vector<std::pair<String, std::vector<String>>>& getFileTypeFilters() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the index of the currently selected file filter
        ///
        /// @return Selected file filter index
        ///
        /// @see setFileTypeFilters
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD std::size_t getFileTypeFiltersIndex() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the text of the open/save button
        ///
        /// @param text  New text of the open/save button
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setConfirmButtonText(const String& text = "Open");


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Return the text of the open/save button
        ///
        /// @return Current caption of the open/save button
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD const String& getConfirmButtonText() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the text of the cancel button (e.g. to display it in a different language)
        ///
        /// @param text  New text to display on the cancel button
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setCancelButtonText(const String& text = "Cancel");


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Return the text of the cancel button
        ///
        /// @return Current caption of the cancel button
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD const String& getCancelButtonText() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the text of the create folder button
        ///
        /// @param text  New text to display on the create folder button
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setCreateFolderButtonText(const String& text = "Create Folder");


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Return the text of the create folder button
        ///
        /// @return Current caption of the create folder button
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD const String& getCreateFolderButtonText() const;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Adds or removes the create folder button
        ///
        /// @param allowCreateFolder Determines if the create folder button should be added or removed (if existing) from the FileDialog
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setAllowCreateFolder(bool allowCreateFolder);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Return whether the file dialog allows the user to create a folder
        ///
        /// @return Boolean value of m_allowCreateFolder
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD bool getAllowCreateFolder() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the text of the filename label (e.g. to display it in a different language)
        ///
        /// @param labelText  New text to display on the label
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setFilenameLabelText(const String& labelText = "Filename:");


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Return the text of the filename label
        ///
        /// @return Current caption of the filename label
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD const String& getFilenameLabelText() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the names of the list view columns (e.g. to display them in a different language)
        ///
        /// @param nameColumnText     Caption to display in the header of the name column
        /// @param sizeColumnText     Caption to display in the header of the size column
        /// @param modifiedColumnText Caption to display in the header of the last modification date column
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setListViewColumnCaptions(const String& nameColumnText = "Name", const String& sizeColumnText = "Size", const String& modifiedColumnText = "Modified");


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the names of the list view columns
        ///
        /// @return Captions displayed in the header of the list view columns
        ///
        /// @see setListViewColumnCaptions
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD std::tuple<String, String, String> getListViewColumnCaptions() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes whether the file should exist or whether the filename can be a non-existent file
        ///
        /// @param enforceExistence  Should the open/save button be disabled when the filename doesn't exist?
        ///
        /// For an open dialog you probably want this set to true (default) while you usually want it false for a save dialog.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setFileMustExist(bool enforceExistence);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns whether the file should exist or whether the filename can be a non-existent file
        ///
        /// @return Should the open/save button be disabled when the filename doesn't exist?
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD bool getFileMustExist() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes whether the file dialog is used for selecting a file or for selecting a directory
        ///
        /// @param selectDirectories  Is the dialog for selecting a directory instead of for selecting a file?
        ///
        /// By default only files can be selected.
        /// When changing this setting to true, only folders will be shown and the file type combo box will be hidden.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSelectingDirectory(bool selectDirectories);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns whether the file dialog is used for selecting a file or for selecting a directory
        ///
        /// @return Is the dialog for selecting a directory instead of for selecting a file?
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD bool getSelectingDirectory() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes whether multiple files can be selected
        ///
        /// @param multiSelect  Can we select multiple files?
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setMultiSelect(bool multiSelect);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns whether multiple files can be selected
        ///
        /// @return Can we select multiple files?
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD bool getMultiSelect() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets a custom icon loader
        ///
        /// @param iconLoader  New icon loader to use
        ///
        /// The icon loader is responsible loading the application icons that are shown next to files and folders.
        /// If no custom icon loader is provided, a default Windows and Linux implementation exists that will use system icons.
        /// On other platforms the default icon loader does nothing and no icons are shown next to the files.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setIconLoader(std::shared_ptr<FileDialogIconLoader> iconLoader);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Gets the icon loader that is currently being used
        ///
        /// @return Current icon loader
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD std::shared_ptr<FileDialogIconLoader> getIconLoader() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void keyPressed(const Event::KeyEvent& event) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Called by the parent of the widget to check if keyPressed would process the event
        ///
        /// @param event  Key event that took place
        ///
        /// @return True if the event would be handled by the widget, false if the key event doesn't affect the widget
        ///
        /// @since TGUI 1.1
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool canHandleKeyPress(const Event::KeyEvent& event) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void textEntered(char32_t key) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves a signal based on its name
        ///
        /// @param signalName  Name of the signal
        ///
        /// @return Signal that corresponds to the name
        ///
        /// @throw Exception when the name does not match any signal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD Signal& getSignal(String signalName) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Function called when one of the properties of the renderer is changed
        ///
        /// @param property  Name of the property that was changed
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void rendererChanged(const String& property) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Saves the widget as a tree node in order to save it to a file
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD std::unique_ptr<DataIO::Node> save(SavingRenderersMap& renderers) const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Loads the widget from a tree of nodes
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void load(const std::unique_ptr<DataIO::Node>& node, const LoadingRenderersMap& renderers) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // This function is called every frame with the time passed since the last frame.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool updateTime(Duration elapsedTime) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Makes a copy of the widget
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD Widget::Ptr clone() const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    private:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Changes the directory that is shown in the dialog
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void changePath(const Filesystem::Path& path, bool updateHistory);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Updates the back and forward buttons when the path history changes
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void historyChanged();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Adds the files to the list view in the order shosen by the user
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void sortFilesInListView();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Stores the selected files and closes the dialog
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void filesSelected(std::vector<Filesystem::Path> filenames);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Updates whether the open/save button is enabled or disabled
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void updateConfirmButtonEnabled();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Handles a press of the open/save button
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void confirmButtonPressed();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Adds a button the File Dialog which allows the user to create a new folder
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void addCreateFolderButton();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Creates a folder in a given directory
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void createFolder(const String& name);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Handles a press of the create folder button
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void createCreateFolderDialog();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Destroys the create folder dialog
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void destroyCreateFolderDialog();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check if the name of a new folder is valid
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool isValidFolderName(const String& name);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Initializes the widget pointers after copying or loading the dialog
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void identifyChildWidgets();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Connects the signals of the child widgets
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void connectSignals();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    public:

        /// One or more files were selected and the confirm button was pressed. This signal fires before onClose.
        /// Optional parameter: selected file or vector of selected files
        /// @see getSelectedPaths
        SignalFileDialogPaths onFileSelect = {"FileSelected"};

        /// The child window was closed or the cancel button was pressed. This signal fires before onClose.
        Signal onCancel = {"Cancelled"};


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        Button::Ptr m_buttonBack;
        Button::Ptr m_buttonForward;
        Button::Ptr m_buttonUp;
        EditBox::Ptr m_editBoxPath;
        ListView::Ptr m_listView;
        Label::Ptr m_labelFilename;
        EditBox::Ptr m_editBoxFilename;
        ComboBox::Ptr m_comboBoxFileTypes;
        Button::Ptr m_buttonCancel;
        Button::Ptr m_buttonConfirm;
        Button::Ptr m_buttonCreateFolder;
        bool m_allowCreateFolder = false;

        bool m_createFolderDialogOpen = false;

        Filesystem::Path m_currentDirectory;
        std::vector<Filesystem::FileInfo> m_filesInDirectory;
        std::vector<Texture> m_fileIcons; // Same order as m_filesInDirectory
        std::size_t m_sortColumnIndex = 0;
        bool m_sortInversed = false;

        std::vector<Filesystem::Path> m_pathHistory;
        std::size_t m_pathHistoryIndex = 0;

        bool m_fileMustExist = true;
        bool m_selectingDirectory = false;
        bool m_multiSelect = false;

        std::vector<std::pair<String, std::vector<String>>> m_fileTypeFilters;
        std::size_t m_selectedFileTypeFilter = 0;

        std::shared_ptr<FileDialogIconLoader> m_iconLoader;

        std::vector<Filesystem::Path> m_selectedFiles;
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_FILE_DIALOG_HPP

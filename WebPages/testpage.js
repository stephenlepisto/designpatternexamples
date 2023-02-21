// JavaScript source code

function get_ancestor_element_by_type(start_element, parent_type) {
    var element = start_element;
    while (element && element.tagName != parent_type) {
        element = element.parentElement;
    }
    return element;
}

// Called on body load, after the page is fully loaded.
//
// Assumptions:
//  - The title of a panel matches exactly the title attribute of the corresponding panel.
//  - Only selection tabs are marked with the class name "tab"
//  - Only panels are marked with the class name "panel"
function onload() {
    let selected_tab = document.getElementsByClassName("tab_selected");
    if (selected_tab.length != 0) {
        // A selection tab as been marked as selected, so make its corresponding
        // panel visible (assumes all panels are hidden by default)
        let panels = document.getElementsByClassName("panel");
        for (let e of panels) {
            if (e.title == selected_tab[0].textContent) {
                e.hidden = false;
                break;
            }
        }
    }
    else {
        // Otherwise, no tab selected so default to selecting the first tab
        let tabs = document.getElementsByClassName("tab")
        if (tabs.length != 0) {
            select_tab(tabs[0])
        }
    }
}


// Called when a tab is clicked on.  Select the tab and show the corresponding
// panel, hiding all other panels.
//
// Assumptions:
//  - The title of a panel matches exactly the title attribute of the corresponding panel.
//  - Only selection tabs are marked with the class name "tab"
//  - Only panels are marked with the class name "panel"
function select_tab(tab) {
    // Search all peer nodes to remove "tab_selected" from the class
    let other_tabs = tab.parentElement.getElementsByClassName("tab");
    for (let e of other_tabs) {
        e.classList.remove("tab_selected");
    }
    // Select the clicked-on tab
    tab.classList.add("tab_selected");
    // Now show the corresponding panel, hiding all other panels.
    let parent_multipanel = get_ancestor_element_by_type(tab, "DIV");
    if (parent_multipanel) {
        panels = parent_multipanel.getElementsByClassName("panel");
        if (panels.length != 0) {
            for (let e of panels) {
                if (e.title == tab.textContent) {
                    e.hidden = false;
                }
                else {
                    e.hidden = true;
                }
            }
        }
    }
}


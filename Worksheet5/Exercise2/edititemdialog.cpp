// edititemdialog.cpp --------------------------------------------------
#include "edititemdialog.h"
#include "ui_edititemdialog.h"
EditItemDialog::EditItemDialog(QWidget *parent) :
QDialog(parent),
ui(new Ui::EditItemDialog) {
    ui->setupUi(this);
    // need to link the ok button to the Dialog's "accept" slot
    connect( ui->okCancelButton, &QDialogButtonBox::accepted, this, &QDialog::accept );
    // need to link the cancel button to the Dialog's "reject" slot
    connect( ui->okCancelButton, &QDialogButtonBox::rejected, this, &QDialog::reject );
}
bool EditItemDialog::runDialog( StockItem & item ) {
    // populate the dialog's input widgets with item's parameters
    ui->itemNameEdit->setText( item.getName() );
    ui->itemCostSpinBox->setValue( item.getUnitCost() );
    ui->itemStockSpinBox->setValue( item.getStockLevel() );
    ui->reorderCheckBox->setChecked( item.getReorder() );

    // get Qt to run the dialog
    if( this->exec() == QDialog::Accepted ) {
        // if user clicked ok, update the item
        item.setName( ui->itemNameEdit->text() );
        item.setUnitCost( ui->itemCostSpinBox->value() );
        item.setStockLevel( ui->itemStockSpinBox->value() );
        item.setReorder( ui->reorderCheckBox->isChecked() );
        return true;
    }

return false;

}

EditItemDialog::~EditItemDialog() {
    delete ui;
}
// ---------------------------------------------------------------------

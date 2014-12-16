//
//  ITableViewBuilder.h
//  DragonVideoPoker
//
//  Created by Ta Van Dung on 8/1/14.
//
//

#ifndef __DragonVideoPoker__ITableViewBuilder__
#define __DragonVideoPoker__ITableViewBuilder__

class ITableCellView;

class ITableViewBuilder {
public:
    virtual ITableCellView* createTableViewCellAt(const int &idx) = 0;
};

#endif /* defined(__DragonVideoPoker__ITableViewBuilder__) */
